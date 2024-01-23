/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:48:08 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/23 02:23:10 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	child(t_cmd *cmd, t_enviroment *enviroment, t_pipe *pipes)
{
	ft_close(&pipes->input_pipe[WRITE_END]);
	ft_close(&pipes->pipes[READ_END]);
	ft_close(&pipes->fd_in);
	ft_close(&pipes->fd_out);
	if (cmd->args[0])
	{
		execve(cmd->args[0], cmd->args,
			(char **)enviroment->variables->toarray(enviroment->variables));
		if (errno == ENOENT)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else
			perror(cmd->args[0]);
	}
	if (!cmd->args[0])
		enviroment->variables->destroy(enviroment->variables, 1);
	else
		enviroment->variables->destroy(enviroment->variables, 0);
	ft_close_pipes(pipes);
	free_cmds(enviroment);
	free(enviroment->child_pid);
	exit(127);
}

static int	launch_cmd(t_cmd **cmd, t_enviroment *enviroment, t_pipe *pipes,
				int i)
{
	if (ft_isbuiltin(cmd[i]))
	{
		setup_signals(IGN);
		enviroment->status = run_builtin(cmd[i], enviroment, pipes);
		ft_close(&pipes->pipes[WRITE_END]);
	}
	else
	{
		enviroment->child_pid[i] = fork();
		if (enviroment->child_pid[i] == 0)
		{
			setup_signals(CHILD);
			child(cmd[i], enviroment, pipes);
		}
		else
			setup_signals(IGN);
	}
	dup2(pipes->fd_out, STDOUT_FILENO);
	ft_close(&pipes->fd_out);
	dup2(pipes->fd_in, STDIN_FILENO);
	ft_close(&pipes->fd_in);
	if (cmd[i]->priorities == AND || cmd[i]->priorities == OR)
		ft_close(&pipes->pipes[READ_END]);
	return (0);
}

static int	redirect_io(t_cmd **cmd, t_pipe *pipes, int i,
				t_enviroment *enviroment)
{
	t_bool	next_cmd_is_pipe;

	if (cmd[i]->has_input_file && !ft_isbuiltin(cmd[i]))
	{
		pipe(pipes->input_pipe);
		if (fill_pipes_with_input(cmd[i], enviroment, pipes) == 5)
			return (5);
		ft_close(&pipes->input_pipe[WRITE_END]);
	}
	if (cmd[i]->has_input_file && !ft_isbuiltin(cmd[i]))
		dup2andclose(&pipes->input_pipe[READ_END], STDIN_FILENO);
	else if (i != 0 && cmd[i]->priorities == PIPE && !ft_isbuiltin(cmd[i]))
		dup2andclose(&pipes->input_for_next, STDIN_FILENO);
	next_cmd_is_pipe = cmd[i + 1] && cmd[i + 1]->priorities == PIPE;
	if (next_cmd_is_pipe || cmd[i]->has_output_file)
		dup2andclose(&pipes->pipes[WRITE_END], STDOUT_FILENO);
	return (0);
}

void	execute_cmds(t_cmd **cmd, t_enviroment *enviroment)
{
	t_pipe	pipes;
	int		i;

	enviroment->child_pid = ft_calloc(enviroment->num_cmd + 1, sizeof(pid_t));
	if (!enviroment->child_pid)
		error_allocating_memory(enviroment);
	innit_pipes(&pipes);
	i = -1;
	while (++i < (int)enviroment->num_cmd)
	{
		if (check_priorities(cmd, enviroment, i, &pipes) == 1)
			continue ;
		save_std_fds(&pipes);
		pipe(pipes.pipes);
		if (redirect_io(cmd, &pipes, i, enviroment) == 5)
			break ;
		launch_cmd(cmd, enviroment, &pipes, i);
		swap_input_for_next(&pipes);
		fill_output_files(cmd[i], enviroment, &pipes);
	}
	ft_close_pipes(&pipes);
	free_cmds(enviroment);
}
