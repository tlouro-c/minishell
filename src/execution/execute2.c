/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:48:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/09 21:40:04 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	run_builtin(t_cmd *cmd, t_enviroment *enviroment, t_pipe *pipes)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = cmd_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = cmd_cd(enviroment, cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = cmd_pwd();
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		status = cmd_export(cmd->args, enviroment);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		status = cmd_unset(cmd->args, enviroment);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		status = cmd_env(cmd->args, enviroment -> variables);
	else if (cmd->args[1] && ft_strcmp(cmd->args[0], "minishell") == 0
		&& ft_strcmp(cmd->args[1], "--help") == 0)
		status = cmd_help();
	else if (cmd->args[1] && ft_strcmp(cmd->args[0], "minishell") == 0
		&& ((ft_strcmp(cmd->args[1], "--short") == 0)
			|| (ft_strcmp(cmd->args[1], "--long") == 0)))
		status = cmd_prompt(cmd, enviroment);
	else
		cmd_exit(cmd->args, enviroment, pipes);
	return (status);
}

static void	swap_cmd(t_cmd **a, t_cmd **b)
{
	t_cmd	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	order_cmd(t_cmd **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i] != NULL && cmd[i - 1] != NULL && cmd[i]->priorities == PIPE
			&& cmd[i]->has_input_file && !cmd[i - 1]->has_input_file)
		{
			j = i;
			while (j > 0 && cmd[j - 1] != NULL && cmd[j - 1]->priorities == PIPE
				&& !cmd[j - 1]->input_file)
			{
				swap_cmd(&cmd[j], &cmd[j - 1]);
				j--;
			}
		}
		i++;
	}
}

void	fill_pipes_with_input(t_cmd *cmd, t_enviroment *enviroment,
			t_pipe *pipes)
{
	int	fd;

	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd == -1)
			error_and_close_pipes(enviroment, pipes);
		if (read_from_to(fd, pipes->input_pipe[WRITE_END]) == -1)
			error_and_close_pipes(enviroment, pipes);
		ft_close(&fd);
	}
	if (cmd -> delimiter)
	{
		if (read_here_doc(cmd->delimiter,
				pipes->input_pipe[WRITE_END]) == -1)
			error_and_close_pipes(enviroment, pipes);
	}
}
