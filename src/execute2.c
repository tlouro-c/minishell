/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:48:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/08 00:22:20 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	run_builtin(t_cmd *cmd, t_enviroment *enviroment)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = cmd_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = cmd_cd(enviroment, cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = cmd_pwd();
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		status = cmd_export(cmd->args, enviroment);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		status = cmd_unset(cmd->args, enviroment);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		status = cmd_env(cmd->args, enviroment -> variables);
	else if (cmd->args[1] && ft_strcmp(cmd->args[0], "minishell") == 0
		&& ft_strcmp(cmd->args[1], "--help") == 0)
		status = cmd_help();
	else if (cmd->args[1] && ft_strcmp(cmd->args[0], "minishell") == 0
		&& ((ft_strcmp(cmd->args[1], "--short") == 0)
			|| (ft_strcmp(cmd->args[1], "--long") == 0)))
		status = cmd_prompt(cmd, enviroment);
	else
		cmd_exit(cmd->args, enviroment);
	return (status);
}
