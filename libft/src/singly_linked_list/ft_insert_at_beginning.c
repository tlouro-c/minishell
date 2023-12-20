/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_at_beginning.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:45:01 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 17:57:55 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_insert_at_beginning(t_node *list, void *content)
{
	t_node	*new;

	new = ft_create_node(content);
	if (new == NULL)
		return (NULL);
	new -> next = list;
	list = new;
	return (new);
}
