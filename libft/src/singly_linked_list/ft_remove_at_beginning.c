/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_at_beginning.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:45:47 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 15:32:04 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_at_beggining(t_node **list)
{
	t_node	*tmp;

	if (list == NULL || *list == NULL)
		return ;
	tmp = *list;
	*list = tmp -> next;
	tmp -> next = NULL;
	free(tmp -> content);
	free(tmp);
}
