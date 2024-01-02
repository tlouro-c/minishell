/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:00:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/02 12:39:08 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_node	*__add2(t_list *this, void *value)
{
	t_node	*new;

	new = (t_node *)ft_calloc(1, sizeof(t_cmd_node));
	if (!new)
		return (NULL);
	new -> destroy = __destroy_node;
	new -> print = __print_node;
	new -> value = value;
	if (this -> begin == NULL)
		this -> begin = new;
	else
		this -> end -> next = new;
	this -> end = new;
	this -> size++;
	((t_list_private *)this)-> needs_update = 1;
	return (new);
}

void	load_commands(t_enviroment *enviroment, char *in)
{
	t_list	*cmds;

	cmds = new_list();
	cmds -> add = __add2;
	in = phase1(in);
	in = phase2(in, enviroment);
	int	i;
	
	i = 0;
	while (in[i])
	{
		if (in[i] == PIPE || in[i] == OR)
			ft_printf("|");
		else if (in[i] == AND)
			ft_printf("&");
		else if (in[i] == SPACE)
			ft_printf(" ");
		else
			ft_printf("%c", in[i]);
		i++;
	}
	ft_printf("\n");
}
