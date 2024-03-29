/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:10:24 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/23 02:27:38 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	free_exit(t_enviroment *enviroment, int status)
{
	free_enviroment(enviroment);
	exit(status);
}

void	free_enviroment(t_enviroment *enviroment)
{
	enviroment->variables->destroy(enviroment->variables, 1);
	if (enviroment->child_pid)
		ft_free((void **)&enviroment->child_pid);
	if (enviroment->cmd)
		free_cmds(enviroment);
}

void	free_cmds(t_enviroment *enviroment)
{
	int	i;

	i = 0;
	while (enviroment->cmd[i])
	{
		free_cmd(enviroment, i);
		i++;
	}
	ft_free((void **)&enviroment->cmd);
}

void	free_cmd(t_enviroment *enviroment, int i)
{
	if (enviroment->cmd[i]->args)
	{
		ft_free_arr((void **)enviroment->cmd[i]->args);
		enviroment->cmd[i]->args = NULL;
	}
	if (enviroment->cmd[i]->input_file)
		enviroment->cmd[i]->input_file->destroy
			(enviroment->cmd[i]->input_file, 1);
	if (enviroment->cmd[i]->output_file)
		enviroment->cmd[i]->output_file->destroy
			(enviroment->cmd[i]->output_file, 1);
	if (enviroment->cmd[i]->append_file)
		enviroment->cmd[i]->append_file->destroy
			(enviroment->cmd[i]->append_file, 1);
	if (enviroment->cmd[i]->delimiter)
		enviroment->cmd[i]->delimiter->destroy
			(enviroment->cmd[i]->delimiter, 1);
	ft_free((void **)&enviroment->cmd[i]);
}

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
