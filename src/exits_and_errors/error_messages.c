/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 01:01:18 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/16 00:08:17 by tlouro-c         ###   ########.fr       */
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

int	msg_parsing_error(char *input, t_enviroment *enviroment)
{
	enviroment->status = 1;
	free(input);
	ft_putstr_fd("Parsing Error\n", 2);
	return (-1);
}

int	msg_command_not_found(t_cmd **cmd, t_enviroment *enviroment)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!cmd[i]->args[0] || (cmd[i]->valid == COMMAND_NOT_FOUND
				&& access(cmd[i]->args[0], X_OK) == -1)
			|| (!ft_isbuiltin(cmd[i]) && access(cmd[i]->args[0], X_OK) == -1))
		{
			enviroment->status = 127;
			if (cmd[i]->args[0])
			{
				ft_putstr_fd(cmd[i]->args[0], 2);
				ft_putstr_fd(": command not found\n", 2);
			}
			free_cmds(enviroment);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	msg_cd_error(char **args, int mode)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(args[1], 2);
	if (mode == 1)
		ft_putstr_fd("HOME not set\n", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	return (1);
}
