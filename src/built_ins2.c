/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:41:40 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 14:27:17 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	bubble_sort(char **arr, int size)
{
	int	i;
	int	j;
	int	swap_count;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		swap_count = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				swap_count++;
				ft_swap_str(&arr[j], &arr[j + 1]);
			}
			j++;
		}
		if (swap_count == 0)
			return ;
		i++;
	}
}

static void	ft_print_list_exported(t_enviroment *enviroment)
{
	t_node	*tmp;
	char	**arr;
	int		i;

	arr = (char **)ft_calloc(enviroment->variables->size + 1, sizeof(char *));
	if (!arr)
		error_allocating_memory(enviroment);
	tmp = enviroment->variables->begin;
	i = 0;
	while (tmp)
	{
		arr[i++] = ft_strdup((const char *)tmp -> value);
		if (!arr[i - 1])
		{
			ft_free_arr((void **)arr);
			error_allocating_memory(enviroment);
		}
		tmp = tmp -> next;
	}
	bubble_sort(arr, enviroment->variables->size);
	i = 0;
	while (arr[i])
		ft_printf("declare -x %s\n", arr[i++]);
	ft_free_arr((void **)arr);
}

int	cmd_export(char **cmd, t_enviroment *enviroment)
{
	int		i;
	int		status;

	status = 0;
	if (cmd[1] == NULL)
		ft_print_list_exported(enviroment);
	else
	{
		i = 0;
		while (cmd[++i] != NULL)
		{
			if ((!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
				|| !ft_key_only_snake(cmd[i]))
			{
				invalid_identifier(cmd[0], cmd[i]);
				status = 1;
				continue ;
			}
			enviroment->variables->removeif
				(enviroment->variables, cmd[i], ft_keycmp);
			enviroment->variables->add(enviroment->variables, (void *)cmd[i]);
		}
	}
	return (status);
}

int	cmd_cd(t_enviroment *enviroment, char **args)
{
	char	*oldpwd;
	char	*pwd;

	if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	oldpwd = ft_strjoin("OLDPWD=", ft_getenv("PWD", enviroment ->variables));
	if (!oldpwd)
		error_allocating_memory(enviroment);
	pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!pwd)
		error_allocating_memory_free_str(enviroment, oldpwd);
	enviroment->variables->set(enviroment->variables, "OLDPWD",
		oldpwd, ft_keycmp);
	free(oldpwd);
	enviroment->variables->set(enviroment->variables, "PWD", pwd, ft_keycmp);
	free(pwd);
	return (0);
}

int	cmd_unset(char **cmd, t_enviroment *enviroment)
{
	int		i;
	int		status;

	if (cmd[1] != NULL && cmd[1][0] == '-')
	{
		invalid_option(cmd[0], cmd[1]);
		return (1);
	}
	i = 0;
	status = 0;
	while (cmd[++i] != NULL)
	{
		if ((!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
			|| !ft_key_only_snake(cmd[i]))
		{
			invalid_identifier(cmd[0], cmd[i]);
			status = 1;
			continue ;
		}
		enviroment->variables->removeif(
			enviroment->variables, (void *)cmd[i], ft_keycmp);
	}
	return (status);
}
