/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:48:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/05 01:09:53 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	manage_output(t_cmd **commands, int (*pipes)[2], int i)
{		
	int	fd;
	
	if (commands[i] -> output_file)
	{
		fd = open(commands[i]->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
		close (pipes[i + 1][1]);
		read_from_to(pipes[i + 1][0], fd);
		ft_putstr_fd("HERE MADAFACKAA\n", 2);
		close(fd);
	}
	ft_putstr_fd("HERE MADAFACKAA\n", 2);
	if (commands[i] -> append_file)
	{
		fd = open(commands[i]->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (-1);
		read_from_to(pipes[i + 1][0], fd);
		close(fd);
	}
	close(pipes[i + 1][0]);
	return (0);
}

void	close_pipes_child(int (*pipes)[2], int i, t_enviroment *enviroment)
{
	int	j;

	j = -1;
	while (++j < (int)enviroment -> num_cmd + 1)
	{
		if (j == i)
			close (pipes[j][1]);
		else if (j == i + 1)
			continue ;
		else
		{
			close (pipes[j][0]);
			close (pipes[j][1]);
		}
	}
}
