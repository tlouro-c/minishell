/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __destroy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:48:53 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/22 20:13:43 by tlouro-c         ###   ########.fr       */
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
		tmp -> destroy(tmp, free_value);
		this -> size--;
		tmp = next;
	}
	ft_free_arr(this -> arr);
	free(this);
}
