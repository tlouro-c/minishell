/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 13:39:19 by tlouro-c         ###   ########.fr       */
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

	if (ft_strarr_size(args) > 1)
	{
		ft_putstr_fd("env: too many arguments", 2);
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

	option = ft_strcmp(args[1], "-n") == 0;
	i = 1 + (option  || args[1][0] == '-');
	while (args[i] != NULL)
		ft_printf("%s ", args[i++]);
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}

void	cmd_exit(char **args, t_enviroment *enviroment)
{
	long long	exit_status;

	exit_status = ft_atoll(args[1]);
	ft_printf("exit\n");
	if (ft_strarr_size(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	if (exit_status > LONG_MAX || exit_status < LONG_MIN || !ft_str_only_digits(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_enviroment(enviroment);
		exit(255);
	}
	else
	{
		free_enviroment(enviroment);
		exit (exit_status % 256);
	}
}

int	cmd_help(void)
{
	ft_printf("minishell - Command List & Help\n\n");
	ft_printf("Built-in commands:\n");
	ft_printf("  ◦ echo with option -n\n");
	ft_printf("  ◦ cd with only a relative or absolute path\n");
	ft_printf("  ◦ pwd with no options\n");
	ft_printf("  ◦ export with no options\n");
	ft_printf("  ◦ unset with no options\n");
	ft_printf("  ◦ env with no options or arguments\n");
	ft_printf("  ◦ exit with no options\n");
	ft_printf("  ◦ minishell --help\n\n");
	printf("Other functionalities replicate Bash commands.\n");
	printf("Use 'man bash' for detailed information.\n");
	return (0);
}

