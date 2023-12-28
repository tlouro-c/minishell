/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:22:59 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/28 17:31:52 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*__add(t_list *this, void *value)
{
	t_node	*new;

	new = new_node();
	if (!new)
		return (NULL);
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
