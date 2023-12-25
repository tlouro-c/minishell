/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:41:40 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/25 01:28:03 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	ft_print_list_exported(t_node *list, char format_specifier)
{
	t_node	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		ft_printf("declare -x ");
		if (format_specifier == 'i' || format_specifier == 'd')
			ft_printf("%i\n", tmp->content);
		else if (format_specifier == 's')
			ft_printf("%s\n", tmp->content);
		tmp = tmp -> next;
	}
}

void	cmd_export(char **cmd, t_enviroment *enviroment)
{
	int	i;
	
	if (cmd[1] == NULL)
		ft_print_list_exported(enviroment -> variables, 's');
	else
	{
		if (cmd[1][0] == '-')
		{
			invalid_option(cmd[0], cmd[1]);
			return ;
		}
		i = 0;
		while (cmd[++i] != NULL)
		{
			if (!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
			{
				invalid_identifier(cmd[0], cmd[i]);
				continue ;
			}
			if (ft_exists_in_list(&enviroment -> variables, cmd[i], ft_keycmp))
				ft_remove_if(&enviroment -> variables, cmd[i], ft_keycmp);
			ft_insert_at_beginning(&enviroment -> variables, cmd[i]);
		}
		return ;
	}
}
