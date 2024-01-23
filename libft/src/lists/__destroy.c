/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __destroy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:48:53 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/23 00:37:05 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__destroy(t_list *this, int free_value)
{
	t_node	*tmp;
	t_node	*next;

	tmp = this -> begin;
	while (tmp)
	{
		next = tmp -> next;
		if (free_value)
			free(tmp->value);
		free(tmp);
		this -> size--;
		tmp = next;
	}
	ft_free_arr(this -> arr);
	free(this);
}
