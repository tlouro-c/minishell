/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __remove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 00:01:58 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 16:14:49 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__removeif(t_list *this, void *data_ref,
			int (*cmp)(void *value, void *data_ref))
{
	t_node	*previous;
	t_node	*tmp;

	if (this -> size < 1)
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
		tmp = previous -> next;
		while (tmp && cmp(tmp -> value, data_ref) == 0)
		{
			previous -> next = tmp -> next;
			tmp -> destroy(tmp);
			this -> size--;
			tmp = previous -> next;
		}
		previous = previous -> next;
	}
}
