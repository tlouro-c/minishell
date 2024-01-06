/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:45:05 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 20:41:55 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_isbuiltin(t_cmd *cmd)
{
	return (ft_strcmp(cmd->args[0], "echo") == 0
		|| ft_strcmp(cmd->args[0], "cd") == 0
		|| ft_strcmp(cmd->args[0], "pwd") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0
		|| ft_strcmp(cmd->args[0], "unset") == 0
		|| ft_strcmp(cmd->args[0], "env") == 0
		|| (cmd->args[1] && ft_strcmp(cmd->args[0], "minishell") == 0
			&& ft_strcmp(cmd->args[1], "--help") == 0)
		|| ft_strcmp(cmd->args[0], "exit") == 0);
}

int	ft_key_only_snake(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isdigit(s[i]) && !ft_isalpha(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) < 0)
			return (-1);
		fd = -1;
	}
	return (0);
}

int	ft_close_pipes(t_pipe pipes)
{
	if (ft_close(pipes.pipes[0]) < 0)
		return (-1);
	if (ft_close(pipes.pipes[1]) < 0)
		return (-1);
	if (ft_close(pipes.input_for_next) < 0)
		return (-1);
	if (ft_close(pipes.input_pipe[0]) < 0)
		return (-1);
	if (ft_close(pipes.input_pipe[1]) < 0)
		return (-1);
	return (0);
}
