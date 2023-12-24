/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/24 12:26:56 by tlouro-c         ###   ########.fr       */
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

void	cmd_env(t_node *enviroment_variables)
{
	ft_print_list(enviroment_variables, 's');
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

void	cmd_unset(char *key, t_enviroment *enviroment)
{
	ft_remove_if(&enviroment -> variables, (void *)key, ft_keycmp);
}
