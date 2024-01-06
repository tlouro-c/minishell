/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:45:05 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 13:33:26 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

size_t	ft_strarr_size(char **strarr)
{
	int	size;

	if (strarr == NULL)
		return (0);
	size = 0;
	while (strarr[size] != NULL)
		size++;
	return (size);
}

int	ft_isbuiltin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
			|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
			|| ft_strcmp(cmd, "exit") == 0);
}

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
	else
		cmd_exit(cmd->args, enviroment);
	return (status);
}

int	ft_strcmp_heredoc(const char *s1, const char *s2)
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

// void	execute_cmd(t_enviroment *enviroment)
// {
// 	//!TODO
// 	execve("path", a, enviroment->variables->arr);
// }
