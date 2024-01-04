/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:48:08 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 11:38:14 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	child(t_cmd *cmd, t_enviroment *enviroment, int *pipes[2], int *i)
{
	
}

void	execute_cmds(t_cmd **commands, t_enviroment *enviroment)
{
	int		*pipes[2];
	int		i;
	pid_t	pid;

	pipes[2] = ft_calloc(enviroment->num_pipes, sizeof(pipes[2]));
	if (!pipes[2])
		error_allocating_memory(enviroment);
	i = 0;
	while (i < enviroment->num_pipes)
		if (pipe(pipes[i++][2]) < 0)
			error_piping(enviroment, pipes[2]);
	i = 0;
	while (i < enviroment->num_cmd)
	{
		if ((enviroment->cmd[i]->priorities == AND && enviroment->status != 0)
			|| (enviroment->cmd[i]->priorities == OR && enviroment->status == 0)
			|| (enviroment->cmd[i]->priorities == PIPE && enviroment->status != 0))
			continue ;
		pid = fork();
		//! PROTECT
		if (pid == 0)
			child(enviroment->cmd[i], enviroment, pipes, i);
		waitpid(pid, enviroment->status, 0);
		enviroment->status = WEXITSTATUS(enviroment->status);
	}
}
