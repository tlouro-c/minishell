/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 14:29:47 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	cmd_pwd(char **args)
{
	char	*pwd;

	if (ft_strarr_size(args) > 2)
	{
		ft_putstr_fd("pwd: too many arguments", 2);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	cmd_env(char **args, t_list *variables)
{
	t_node	*tmp;

	if (ft_strarr_size(args) > 1)
	{
		ft_putstr_fd("env: too many arguments", 2);
		return (1);
	}
	tmp = variables -> begin;
	while (tmp)
	{
		if (ft_strrchr((char *)tmp -> value, '='))
			tmp -> print(tmp, 's');
		tmp = tmp -> next;
	}
	return (0);
}

int	cmd_echo(char **args)
{
	int	option;
	int	i;

	option = ft_strcmp(args[1], "-n") == 0;
	i = 1 + option;
	while (args[i] != NULL)
	{
		ft_printf("%s ", args[i]);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}

void	cmd_exit(char **args, t_enviroment *enviroment)
{
	long long	exit_status;

	if (ft_strarr_size(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	exit_status = ft_atoll(args[1]);
	if (exit_status > LONG_MAX || exit_status < LONG_MIN)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return ;
	}
	else
	{
		free_enviroment(enviroment);
		exit (exit_status % 256);
	}
}

int	cmd_unset(char **cmd, t_enviroment *enviroment)
{
	char	*key;
	int		i;

	if (cmd[1] != NULL && cmd[1][0] == '-')
	{
		invalid_option(cmd[0], cmd[1]);
		return (1);
	}
	i = 1;
	while (cmd[i] != NULL)
	{
		key = cmd[i];
		enviroment->variables->removeif(
			enviroment->variables, (void *)key, ft_keycmp);
		i++;
	}
	return (0);
}
