/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:41:40 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/09 18:01:31 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
		arr[i++] = get_env_declare((char *)tmp -> value);
		if (!arr[i - 1])
		{
			ft_free_arr((void **)arr);
			error_allocating_memory(enviroment);
		}
		tmp = tmp -> next;
	}
	ft_quick_sort_str(arr, enviroment->variables->size);
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
			enviroment->variables->add(enviroment->variables,
				(void *)ft_strdup(cmd[i]));
		}
	}
	return (status);
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

int	cmd_help(void)
{
	ft_printf("minishell - Command List & Help\n\n");
	ft_printf("Built-in commands:\n");
	ft_printf("  ◦ echo\t\t\t\twith option -n\n");
	ft_printf("  ◦ cd\t\t\t\t\twith only a relative or absolute path\n");
	ft_printf("  ◦ pwd\t\t\t\t\twith no options\n");
	ft_printf("  ◦ export\t\t\t\twith no options\n");
	ft_printf("  ◦ unset\t\t\t\twith no options\n");
	ft_printf("  ◦ env\t\t\t\t\twith no options or arguments\n");
	ft_printf("  ◦ exit\t\t\t\twith no options\n");
	ft_printf("  ◦ minishell --help\t\t\tDisplay help message\n");
	ft_printf("  ◦ minishell --short\t\t\tDisplay a short prompt\n");
	ft_printf("  ◦ minishell --long\t\t\tDisplay current user and"
		" current path on prompt\n\n");
	ft_printf("Other functionalities replicate Bash commands.\n");
	ft_printf("Use 'man bash' for detailed information.\n");
	return (0);
}

int	cmd_prompt(t_cmd *cmd, t_enviroment *enviroment)
{
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "--short") == 0)
	{
		enviroment->prompt_mode = SHORT;
		return (0);
	}
	else if (cmd->args[1] && ft_strcmp(cmd->args[1], "--long") == 0)
	{
		enviroment->prompt_mode = LONG;
		return (0);
	}
	return (0);
}
