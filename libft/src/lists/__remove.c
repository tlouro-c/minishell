/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __remove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:01:58 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 15:27:05 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	remove_while(t_list *this, t_node *previous, void *data_ref,
			int (*cmp)(void *value, void *data_ref))
{
	t_node	*tmp;

	tmp = previous -> next;
	while (tmp && cmp(tmp -> value, data_ref) == 0)
	{
		if (tmp == this -> end)
			this -> end = previous;
		previous -> next = tmp -> next;
		tmp -> destroy(tmp);
		this -> size--;
		tmp = previous -> next;
	}
}

void	__removeif(t_list *this, void *data_ref,
			int (*cmp)(void *value, void *data_ref))
{
	t_node	*previous;
	t_node	*tmp;

	if (!this || !this -> begin || !cmp)
		return ;
	while (this -> begin && cmp(this -> begin -> value, data_ref) == 0)
	{
		tmp = this -> begin;
		this -> begin = tmp -> next;
		tmp -> destroy(tmp);
		this -> size--;
	}
	previous = this -> begin;
	while (previous && previous -> next)
	{
		remove_while(this, previous, data_ref, cmp);
		previous = previous -> next;
	}
	((t_list_private *)this)-> needs_update = 1;
}
