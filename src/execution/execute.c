/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:48:08 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/10 18:30:37 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	child(t_cmd *cmd, t_enviroment *enviroment, t_pipe *pipes)
{
	ft_close(&pipes->pipes[READ_END]);
	execve(cmd->args[0], cmd->args,
		(char **)enviroment->variables->toarray(enviroment->variables));
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		perror(cmd->args[0]);
	ft_close_pipes(pipes);
	free_enviroment(enviroment);
	exit(127);
}

static int	launch_cmd(t_cmd **cmd, t_enviroment *enviroment, t_pipe *pipes,
				int i)
{
	if (ft_isbuiltin(cmd))
	{
		setup_signals(IGN);
		enviroment->status = run_builtin(cmd, enviroment);
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
	return (0);
}

static void	redirect_output(t_cmd **cmd, t_pipe *pipes, int i)
{
	t_bool	has_output_file;
	t_bool	next_cmd_is_pipe;

	has_output_file = cmd[i]->append_file || cmd[i]->output_file;
	next_cmd_is_pipe = cmd[i + 1] && cmd[i + 1]->priorities == PIPE;
	if (next_cmd_is_pipe || has_output_file)
	{
		dup2(pipes->pipes[WRITE_END], STDOUT_FILENO);
		ft_close(&pipes->pipes[WRITE_END]);
	}
}

static void	redirect_input(t_cmd *cmd, t_pipe *pipes, int i,
	t_enviroment *enviroment)
{
	if (cmd->has_input_file)
		pipe(pipes->input_pipe);
	if (cmd->has_input_file && i != 0 && cmd->priorities == PIPE)
		if (read_from_to(pipes->input_for_next,
				pipes->input_pipe[WRITE_END]) < 0)
			error_and_close_pipes(enviroment, pipes);
	fill_pipes_with_input(cmd, enviroment, pipes);
	if (cmd->has_input_file)
		ft_close(&pipes->input_pipe[1]);
	if (cmd->has_input_file)
	{
		dup2(pipes->input_pipe[READ_END], STDIN_FILENO);
		ft_close(&pipes->input_pipe[READ_END]);
	}
	else if (i != 0 && cmd->priorities == PIPE)
		dup2(pipes->input_for_next, STDIN_FILENO);
	ft_close(&pipes->input_for_next);
}

void	execute_cmds(t_cmd **cmd, t_enviroment *enviroment)
{
	t_pipe	pipes;
	int		i;

	innit_pipes(&pipes);
	if (msg_command_not_found(cmd, enviroment) == -1)
		return ;
	i = -1;
	while (++i < (int)enviroment->num_cmd)
	{
		if (check_priorities(cmd, enviroment, i) == 1)
			continue ;
		pipes.fd_in = dup(STDIN_FILENO);
		pipes.fd_out = dup(STDOUT_FILENO);
		pipe(pipes.pipes);
		redirect_input(cmd[i], &pipes, i, enviroment);
		redirect_output(cmd, &pipes, i);
		launch_cmd(cmd, enviroment, &pipes, i);
		pipes.input_for_next = pipes.pipes[READ_END];
		fill_output_files(cmd[i], enviroment, &pipes);
		free_cmd(enviroment, i);
	}
	ft_close_pipes(&pipes);
	ft_free((void **)&enviroment->cmd);
}
