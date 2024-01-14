/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:48:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/14 13:41:41 by tlouro-c         ###   ########.fr       */
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

int	fill_pipes_with_input(t_cmd *cmd, t_enviroment *enviroment,
			t_pipe *pipes)
{
	int	status;
	int	fd;

	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->input_file);
			return (5);
		}
		if (read_from_to(fd, pipes->input_pipe[WRITE_END]) == -1)
			error_and_close_pipes(enviroment, pipes);
		ft_close(&fd);
	}
	if (cmd -> delimiter)
	{
		status = read_here_doc(cmd->delimiter, pipes->input_pipe[WRITE_END],
				enviroment);
		if (status == -1)
			error_and_close_pipes(enviroment, pipes);
		else if (status == -2)
			return (5);
	}
	return (0);
}

void	wait_loop(t_enviroment *enviroment)
{
	int	i;
	int	status;

	i = 0;
	while (enviroment->child_pid[i])
	{
		waitpid(enviroment->child_pid[i], &status, 0);
		enviroment->status = WEXITSTATUS(status);
		i++;
	}
	wait(NULL);
	ft_free((void **)&enviroment->child_pid);
}

void	save_std_fds(t_pipe *pipes)
{
	pipes->fd_in = dup(STDIN_FILENO);
	pipes->fd_out = dup(STDOUT_FILENO);
}

void	swap_input_for_next(t_pipe *pipes)
{
	ft_close(&pipes->input_for_next);
	pipes->input_for_next = pipes->pipes[READ_END];
}
