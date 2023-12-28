/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/28 17:36:47 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
}

void	cmd_env(t_list *variables)
{
	t_node	*tmp;

	tmp = variables -> begin;
	while (tmp)
	{
		if (ft_strrchr((char *)tmp -> value, '='))
			tmp -> print(tmp, 's');
		tmp = tmp -> next;
	}
}

void	cmd_echo(char **args)
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

void	cmd_unset(char **cmd, t_enviroment *enviroment)
{
	char	*key;
	int		i;

	if (cmd[1] != NULL && cmd[1][0] == '-')
	{
		invalid_option(cmd[0], cmd[1]);
		return ;
	}
	i = 1;
	while (cmd[i] != NULL)
	{
		key = cmd[i];
		enviroment->variables->removeif(
			enviroment->variables, (void *)key, ft_keycmp);
		i++;
	}
}
