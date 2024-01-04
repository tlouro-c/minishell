/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:48:08 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 20:09:49 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	child(t_cmd *cmd, t_enviroment *enviroment, int (*pipes)[2], int i)
{
	char	**envp;



	if (cmd->priorities == OR)
	{
		(void)i;
		(void)pipes;
	}
		// dup2(pipes[i][0], STDIN_FILENO);
	// dup2(pipes[i + 1][1], STDOUT_FILENO);
	else
	{
		envp = (char **)enviroment->variables->toarray(enviroment->variables);
		execve(cmd->args[0], cmd->args, envp);
		if (errno == ENOENT)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit (127);
		}
		else
			perror(cmd->args[0]);
	}
		
		
}

static int	read_here_doc(char *delimiter, int to_fd)
{
	char	*line;

	while (1)
	{
		line = ft_get_next_line_v2(0);
		if (!line)
			return (-1);
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (write(to_fd, line, ft_strlen(line)) < 0)
			return (-1);
		free(line);
	}
	return (0);
}

static int	read_from_to(int from_fd, int to_fd)
{
	char	buffer[1024];
	size_t	bytes_read;
	
	while (1)
	{
		bytes_read = read(from_fd, buffer, 1024);
		if (bytes_read < 0)
		{
			close(from_fd);
			return (-1);
		}
		else if (bytes_read == 0)
		{
			close(from_fd);
			return (0);
		}
		if (write (to_fd, buffer, bytes_read) < 0)
		{
			close(from_fd);
			return (-1);
		}
	}
}

static void launch_cmd(t_cmd *command, t_enviroment *enviroment, int (*pipes)[2], int i)
{
	pid_t	pid;
	int		fd;

	if (command->delimiter != NULL)
		if (read_here_doc(command->delimiter, pipes[i][1]) < 0)
			error_and_close_pipes(enviroment, pipes);
	if (command->input_file != NULL)
	{
		fd = open(command->input_file, O_RDONLY, 0666);
		if (fd < 0 || read_from_to(fd, pipes[i][1]) < 0)
			error_and_close_pipes(enviroment, &pipes[2]);
	}
	if (i == 0 && command->input_file == NULL && command->delimiter == NULL)
		dup2(STDIN_FILENO, pipes[i][1]);
	if (ft_isbuiltin(command->args[0]))
	{
		enviroment->status = (run_builtin(command, enviroment));
		return ;
	}
	pid = fork();
	//! PROTECT
	if (pid == 0)
		child(command, enviroment, pipes, i);
	waitpid(pid, (int *)&enviroment->status, 0);
	enviroment->status = WEXITSTATUS(enviroment->status);
}

void	execute_cmds(t_cmd **commands, t_enviroment *enviroment)
{
	int		(*pipes)[2];
	int		i;

	pipes = ft_calloc(enviroment->num_cmd + 1, sizeof(pipes));
	if (!pipes)
		error_allocating_memory(enviroment);
	i = 0;
	while (i < (int)enviroment->num_cmd + 1)
		if (pipe(pipes[i++]) < 0)
			error_piping(enviroment, pipes);
	i = -1;
	while (++i < (int)enviroment->num_cmd)
	{
		if ((commands[i]->priorities == AND && enviroment->status != 0)
			|| (commands[i]->priorities == OR && enviroment->status == 0)
			|| (commands[i]->priorities == PIPE
				&& enviroment->status != 0 && i != 0))
			continue ;
		launch_cmd(commands[i], enviroment, pipes, i); 
	}
}
