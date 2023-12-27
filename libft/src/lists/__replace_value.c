/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __replace_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:37:24 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 16:47:49 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__replace(t_list *this, void *data_ref, void *new_value,
			int (*cmp)(void *value, void *data_ref))
{
	t_node	*tmp;

	tmp = this -> begin;
	while (tmp)
	{
		if (cmp(tmp -> value, data_ref) == 0)
		{
			free(tmp -> value);
			tmp -> value = new_value;
		}
		tmp = tmp -> next;
	}
}
