/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:00:45 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/16 13:32:57 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_strcmp_heredoc(char *line, const char *delimiter)
{
	int		i;
	int		result;

	i = 0;
	while (delimiter[i] && line[i] && line[i] == delimiter[i])
		i++;
	result = line[i] == '\n' && delimiter[i] == '\0';
	return (1 - result);
}

int	read_here_doc(t_list *delimiter, int to_fd, t_enviroment *enviroment)
{
	char	*line;
	t_node	*tmp;

	tmp = delimiter->begin;
	while (tmp)
	{
		ft_printf("> ");
		line = ft_get_next_line(0);
		if (!line)
			return (-2);
		if (ft_strcmp_heredoc(line, (char *)tmp->value) == 0)
		{
			tmp = tmp->next;
			free(line);
			continue ;
		}
		line = exp_here_doc(line, enviroment);
		if (!line)
			return (-1);
		if (tmp == delimiter->end)
			write(to_fd, line, ft_strlen(line));
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
