/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:00:45 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/24 00:03:31 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_strcmp_heredoc(char *line, char *delimiter, t_node **tmp)
{
	char	*delimiter_trimmed;
	int		i;
	int		result;

	delimiter_trimmed = ft_strshrinker(delimiter, "\a\e\5\6", 0);
	i = 0;
	while (delimiter_trimmed[i] && line[i] && line[i] == delimiter_trimmed[i])
		i++;
	result = line[i] == '\n' && delimiter_trimmed[i] == '\0';
	if (result)
	{
		*tmp = (*tmp)->next;
		free(line);
	}
	free(delimiter_trimmed);
	return (1 - result);
}

int	read_here_doc(t_list *delimiter, int to_fd, t_enviroment *enviroment,
		int prio)
{
	char	*line;
	t_node	*tmp;
	int		exp;

	tmp = delimiter->begin;
	while (tmp)
	{
		exp = ((char *)tmp->value)[0] == '\e';
		ft_printf("> ");
		line = ft_get_next_line(0);
		if (!line)
			return (-2);
		if (ft_strcmp_heredoc(line, (char *)tmp->value, &tmp) == 0)
			continue ;
		if (!exp)
			line = exp_here_doc(line, enviroment);
		if (!line)
			return (-1);
		if (prio == HERE && tmp == delimiter->end)
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

static int	_output_file(t_cmd *cmd, t_node *file, t_pipe *pipes,
	int mode)
{
	int	fd;
	int	status;

	status = 0;
	if (mode == O_TRUNC)
		fd = open((char *)file->value,
				O_CREAT | O_TRUNC | O_RDWR, 0666);
	else
		fd = open((char *)file->value,
				O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd < 0)
		return (-1);
	if ((cmd->prio_out == APP && mode == O_APPEND
			&& cmd->append_file->end == file)
		|| (cmd->prio_out == OVE && mode == O_TRUNC
			&& cmd->output_file->end == file))
	{
		status = read_from_to(pipes->input_for_next, fd);
		if (status < 0)
			return (-1);
	}
	ft_close(&fd);
	return (0);
}

void	fill_output_files(t_cmd *cmd, t_enviroment *enviroment, t_pipe *pipes)
{
	t_node	*tmp;

	tmp = cmd->output_file->begin;
	while (tmp)
	{
		if (_output_file(cmd, tmp, pipes, O_TRUNC) == -1)
			error_and_close_pipes(enviroment, pipes);
		tmp = tmp->next;
	}
	tmp = cmd->append_file->begin;
	while (tmp)
	{
		if (_output_file(cmd, tmp, pipes, O_APPEND) == -1)
			error_and_close_pipes(enviroment, pipes);
		tmp = tmp->next;
	}
}
