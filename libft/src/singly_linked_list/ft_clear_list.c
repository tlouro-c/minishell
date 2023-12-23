/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:02:22 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/23 12:05:17 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_list(t_node **list)
{
	t_node	*tmp;
	t_node	*next;

	if (list == NULL)
		return ;
	tmp = *list;
	while (tmp != NULL)
	{
		next = tmp -> next;
		tmp -> next = NULL;
		free(tmp -> content);
		free(tmp);
		tmp = next;
	}
}
