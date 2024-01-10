/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:00:45 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/10 20:30:48 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_strcmp_heredoc(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1[i] == '\n' && s2[i] == '\n')
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' )
	{
		if (s1[i + 1] == '\n')
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

int	read_here_doc(char *delimiter, int to_fd)
{
	char	*line;

	while (1)
	{
		ft_printf("> ");
		line = ft_get_next_line(0);
		if (!line)
			return (-1);
		if (ft_strcmp_heredoc(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write(to_fd, line, ft_strlen(line)) < 0)
			return (-1);
		free(line);
	}
	return (0);
}

int	read_from_to(int from_fd, int to_fd)
{
	char	buffer[PIPE_BUF];
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

static void	_output_file(t_cmd *cmd, t_enviroment *enviroment, t_pipe *pipes,
	int mode)
{
	int	fd;
	int	status;

	if (mode == O_TRUNC)
		fd = open(cmd->output_file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	else
		fd = open(cmd->append_file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd < 0)
		error_and_close_pipes(enviroment, pipes);
	status = read_from_to(pipes->input_for_next, fd);
	ft_close(&fd);
	if (status < 0)
		error_and_close_pipes(enviroment, pipes);
}

void	fill_output_files(t_cmd *cmd, t_enviroment *enviroment, t_pipe *pipes)
{
	if (cmd->output_file)
		_output_file(cmd, enviroment, pipes, O_TRUNC);
	if (cmd->append_file)
		_output_file(cmd, enviroment, pipes, O_APPEND);
}
