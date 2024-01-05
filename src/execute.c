/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:48:08 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/05 15:20:10 by tlouro-c         ###   ########.fr       */
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

// static int	read_here_doc(char *delimiter, int to_fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = ft_get_next_line_v2(0);
// 		if (!line)
// 			return (-1);
// 		if (ft_strcmp(line, delimiter) == 0)
// 			break ;
// 		if (write(to_fd, line, ft_strlen(line)) < 0)
// 			return (-1);
// 		free(line);
// 	}
// 	return (0);
// }

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
	}
	
}

static void	wait_loop(t_enviroment *enviroment)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	while (i < (int)enviroment->num_cmd)
	{
		wait(&status);
		enviroment->status = WEXITSTATUS(status);
		i++;
	}
}

static void redirect_output(t_cmd **cmd, t_pipe pipes, int i, t_enviroment *enviroment)
{
	(void)cmd;
	//? Implement redirections
	enviroment->fd_out = dup(STDOUT_FILENO);
	if (i != (int)enviroment->num_cmd -1)
		dup2(pipes.pipes[WRITE_END], STDOUT_FILENO);
}

static void redirect_input(t_cmd **cmd, t_pipe pipes, int i, t_enviroment *enviroment)
{
	(void)enviroment;
	(void)i;
	(void)cmd;
	//? Implement redirections
	enviroment->fd_in = dup(STDIN_FILENO);
	dup2(pipes.input_for_next, STDIN_FILENO);
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
		redirect_input(cmd, pipes, i, enviroment);
		redirect_output(cmd, pipes, i, enviroment);
		launch_cmd(cmd[i], enviroment, pipes);
		close (pipes.pipes[WRITE_END]);
		pipes.input_for_next = pipes.pipes[READ_END];
		dup2(enviroment->fd_out, STDOUT_FILENO);
		dup2(enviroment->fd_in, STDIN_FILENO);
	}
	wait_loop(enviroment);
}

