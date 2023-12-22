/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_at_beginning.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:45:01 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/21 23:19:28 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_insert_at_beginning(t_node **list, void *content)
{
	t_node	*new;

	new = (t_node *)ft_calloc(1, sizeof(t_node));
	if (new == NULL)
		return (NULL);
	new -> content = content;
	new -> next = *list;
	*list = new;
	return (new);
}
