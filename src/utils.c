/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:45:05 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 14:33:05 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*path_for_prompt(t_enviroment *enviroment)
{
	char	*path;

	path = ft_getenv("PWD", enviroment->variables)
		+ ft_strlen(ft_getenv("HOME", enviroment->variables));
	return (path);
}

char	*user_prompt(t_enviroment *enviroment)
{
	char	*str_to_join[6];
	char	*prompt;
	char	*tmp;
	int		i;

	if (enviroment -> prompt != NULL)
		free(enviroment -> prompt);
	prompt = NULL;
	str_to_join[0] = "\e[1;95m";
	str_to_join[1] = ft_getenv("USER", enviroment->variables);
	str_to_join[2] = "@minishell:\e[1;96m~";
	str_to_join[3] = path_for_prompt(enviroment);
	str_to_join[4] = "$ \e[0m";
	str_to_join[5] = NULL;
	i = -1;
	while (str_to_join[++i] != NULL)
	{
		tmp = prompt;
		prompt = ft_strjoin(prompt, str_to_join[i]);
		free(tmp);
		if (prompt == NULL)
			error_allocating_memory(enviroment);
	}
	return (prompt);
}

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

void	run_builtin(t_cmd *cmd, t_enviroment *enviroment)
{
	int	status;

	if (ft_strcmp(cmd, "echo") == 0)
		status = cmd_echo(cmd->args);
	else if (ft_strcmp(cmd, "cd") == 0)
		status = cmd_cd(enviroment, cmd->args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		status = cmd_pwd(cmd->args);
	else if (ft_strcmp(cmd, "export") == 0)
		status = cmd_export(cmd->args, enviroment);
	else if (ft_strcmp(cmd, "unset") == 0)
		status = cmd_unset(cmd->args, enviroment);
	else if (ft_strcmp(cmd, "env") == 0)
		status = cmd_env(cmd, enviroment -> variables);
	else
		cmd_exit(cmd->args, enviroment);
	enviroment -> status = status;
}

// void	execute_cmd(t_enviroment *enviroment)
// {
// 	//!TODO
// 	execve("path", a, enviroment->variables->arr);
// }
