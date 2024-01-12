/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/12 20:14:05 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	cmd_env(char **args, t_list *variables)
{
	t_node	*tmp;

	if (ft_arr_size((void **)args) > 1)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	tmp = variables -> begin;
	while (tmp)
	{
		if (ft_strchr((char *)tmp -> value, '='))
			tmp -> print(tmp, 's');
		tmp = tmp -> next;
	}
	return (0);
}

int	cmd_echo(char **args)
{
	int	option;
	int	i;

	i = 1;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	option = echo_strcmp(args[1]) == 0;
	while (args[i] != NULL && echo_strcmp(args[i]) == 0)
		i++;
	while (args[i] != NULL)
		ft_printf("%s ", args[i++]);
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}

void	cmd_exit(char **args, t_enviroment *enviroment, t_pipe *pipes)
{
	long long	exit_status;

	ft_printf("exit\n");
	exit_status = ft_atoll(args[1]);
	if (ft_arr_size((void **)args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	if (exit_status > LONG_MAX || exit_status < LONG_MIN
		|| (args[1] && !ft_str_only_digits(args[1])))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_enviroment(enviroment);
		exit(255);
	}
	else
	{
		ft_close_pipes(pipes);
		free_enviroment(enviroment);
		exit (exit_status % 256);
	}
}

int	cmd_cd(t_enviroment *enviroment, char **args)
{
	if (!args[1] || args[1][0] == '~')
	{
		if (chdir(ft_getenv("HOME", enviroment->variables)) != 0)
			return (msg_cd_error(args, 1));
	}
	else
		if (chdir(args[1]) != 0)
			return (msg_cd_error(args, 0));
	if (ft_getenv("OLDPWD", enviroment->variables)[0] != '\0')
		set_oldpwd(enviroment);
	if (ft_getenv("PWD", enviroment->variables)[0] != '\0')
		set_pwd(enviroment);
	return (0);
}
