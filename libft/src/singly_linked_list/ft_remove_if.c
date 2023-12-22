/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:56:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 16:19:58 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_if(t_node **list, void *ref,
			int (*cmp)(void *content, void *ref))
{
	t_node	*previous;
	t_node	*tmp;

	if (list == NULL || *list == NULL)
		return ;
	while (*list && cmp((*list)->content, ref) == 0)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->content);
		free(tmp);
	}
	previous = *list;
	while (previous)
	{
		while (previous->next && cmp(previous->next->content, ref) == 0)
		{
			tmp = previous->next;
			previous->next = tmp->next;
			free(tmp->content);
			free(tmp);
		}
		previous = previous->next;
	}
}
