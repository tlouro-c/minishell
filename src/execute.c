/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:48:08 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 01:41:57 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	child(t_cmd *cmd, t_enviroment *enviroment, t_pipe pipes)
{
	close (pipes.pipes[0]);
	execve(cmd->args[0], cmd->args, (char **)enviroment->variables->toarray(enviroment->variables));
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	else
		perror(cmd->args[0]);
}

static int	read_here_doc(char *delimiter, int to_fd)
{
	char	*line;

	while (1)
	{
		line = ft_get_next_line(0);
		if (!line)
			return (-1);
		if (ft_strcmp_heredoc(line, delimiter) == 0)
			break ;
		if (write(to_fd, line, ft_strlen(line)) < 0)
			return (-1);
		free(line);
	}
	return (0);
}

int	read_from_to(int from_fd, int to_fd)
{
	char	buffer[1];
	int		bytes_read;

	while (1)
	{
		bytes_read = read(from_fd, buffer, sizeof(buffer));
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			break ;
		if (write(to_fd, buffer, bytes_read) < 0)
			return (-1);
	}
	return (0);
}

static void	launch_cmd(t_cmd *cmd, t_enviroment *enviroment, t_pipe pipes)
{
	int	pid;
	
	if (ft_isbuiltin(cmd->args[0]))
		run_builtin(cmd, enviroment);
	else
	{
		pid = fork();
		if (pid == 0)
			child(cmd, enviroment, pipes);
		waitpid(pid, (int *)&enviroment->status, 0);
		enviroment->status = WEXITSTATUS(enviroment->status);
	}
	
}

// static void	wait_loop(t_enviroment *enviroment)
// {
// 	int		i;
// 	int		status;

// 	status = 0;
// 	i = 0;
// 	while (i < (int)enviroment->num_cmd)
// 	{
// 		wait(&status);
// 		enviroment->status = WEXITSTATUS(status);
// 		i++;
// 	}
// }

static void redirect_output(t_cmd **cmd, t_pipe pipes, int i, t_enviroment *enviroment)
{
	t_bool	has_output_file;
	t_bool	next_cmd_is_pipe;
	
	has_output_file = cmd[i]->append_file || cmd[i]->output_file;
	next_cmd_is_pipe = cmd[i + 1] && cmd[i + 1]->priorities == PIPE;
	enviroment->fd_out = dup(STDOUT_FILENO);
	if (next_cmd_is_pipe || has_output_file)
	{
		dup2(pipes.pipes[WRITE_END], STDOUT_FILENO);
		close(pipes.pipes[WRITE_END]);
	}
}

static void redirect_input(t_cmd *cmd, t_pipe pipes, int i, t_enviroment *enviroment)
{
	if (i != 0 || cmd->input_file || cmd->delimiter)
		pipe(pipes.input_pipe);
	if (i != 0 && cmd -> priorities == PIPE)
		read_from_to(pipes.input_for_next, pipes.input_pipe[WRITE_END]);
	if (cmd->input_file || cmd->delimiter)
	{
		if (cmd->input_file)
			if (read_from_to(open(cmd->input_file, O_RDONLY),
				pipes.input_pipe[WRITE_END]))
				error_allocating_memory(enviroment);
		if (cmd->delimiter)
			if (read_here_doc(cmd->delimiter, pipes.input_pipe[1]) < 0)
				error_allocating_memory(enviroment);
	}
	if (i != 0 || cmd->input_file || cmd->delimiter)
		close (pipes.input_pipe[1]);
	enviroment->fd_in = dup(STDIN_FILENO);
	close (pipes.input_for_next);
	if (cmd->priorities == PIPE && !ft_isbuiltin(cmd->args[0]))
	{
		dup2(pipes.input_pipe[0], STDIN_FILENO);
		close(pipes.input_pipe[0]);
	}
}

static void	fill_output_files(t_cmd *cmd, t_enviroment *enviroment, t_pipe pipes)
{
	int	fd;

	if (cmd->output_file)
	{
		close (STDOUT_FILENO);
		fd = open(cmd->output_file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (read_from_to(pipes.input_for_next, fd) < 0)
			error_allocating_memory(enviroment);
		close(fd);
	}
	if (cmd->append_file)
	{
		close (STDOUT_FILENO);
		fd = open(cmd->output_file, O_CREAT | O_APPEND | O_WRONLY, 0666);
		if (read_from_to(pipes.input_for_next, fd) < 0)
			error_allocating_memory(enviroment);
		close(fd);
	}
}

void	execute_cmds(t_cmd **cmd, t_enviroment *enviroment)
{
	t_pipe	pipes;
	int		i;

	pipes.input_for_next = STDIN_FILENO;
	i = -1;
	while (++i < (int)enviroment->num_cmd)
	{
		if ((cmd[i]->priorities == AND && enviroment->status != 0)
			|| (cmd[i]->priorities == OR && enviroment->status == 0)
			|| (cmd[i]->priorities == PIPE
				&& enviroment->status != 0 && i != 0))
			continue ;
		pipe(pipes.pipes);
		redirect_input(cmd[i], pipes, i, enviroment);
		redirect_output(cmd, pipes, i, enviroment);
		launch_cmd(cmd[i], enviroment, pipes);
		pipes.input_for_next = pipes.pipes[READ_END];
		fill_output_files(cmd[i], enviroment, pipes);
		dup2(enviroment->fd_out, STDOUT_FILENO);
		dup2(enviroment->fd_in, STDIN_FILENO);
	}
	// wait_loop(enviroment);
}

