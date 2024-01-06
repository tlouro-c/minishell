/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 01:01:18 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 17:34:27 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	invalid_option(char *cmd, char *option)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putchar_fd(option[0], 2);
	ft_putchar_fd(option[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
}

void	invalid_identifier(char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	msg_parsing_error(char *input)
{
	free(input);
	ft_putstr_fd("Parsing Error\n", 2);
	return (-1);
}

int	msg_command_not_found(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->valid == COMMAND_NOT_FOUND)
		{
			ft_putstr_fd(cmd[i]->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free_cmds(cmd);
			return (-1);
		}
		i++;
	}
	return (0);
}
