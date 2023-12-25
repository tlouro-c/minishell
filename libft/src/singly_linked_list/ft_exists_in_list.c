/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exists_in_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:20:30 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/24 14:36:35 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_exists_in_list(t_node **list, void *ref,
			int (*cmp)(void *content, void *ref))
{
	t_node	*tmp;

	if (list == NULL || *list == NULL)
		return (0);
	tmp = *list;
	while (tmp != NULL)
	{
		if (cmp(tmp -> content, ref) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
