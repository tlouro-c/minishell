/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:34:46 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 15:36:31 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_list_size(t_node *list)
{
	t_node	*tmp;
	size_t	size;

	size = 0;
	tmp = list;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp -> next;
	}
	return (size);
}
