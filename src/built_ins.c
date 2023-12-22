/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 17:34:05 by tlouro-c         ###   ########.fr       */
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

static int	ft_atoi_exit(char *s)
{
	int	n;
	int	i;
	int	negative;

	if (s == NULL)
		return (0);
	n = 0;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	negative = s[i] == '-';
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] != '\0' && ft_isdigit(s[i]))
	{
		n = n * 10 + (s[i++] - '0');
		if (n >= 256)
			n = 0 + (n - 256);
	}
	if (negative)
		return (n * -1);
	return (n);
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
		(void)enviroment;
		//! FREE EVERYTHING BEFORE EXTING
		exit (ft_atoi_exit(args[1]));
	}
}
