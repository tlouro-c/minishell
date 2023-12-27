/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __destroy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:48:53 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 16:21:12 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__destroy(t_list *this)
{
	t_node	*tmp;
	t_node	*next;

	tmp = this -> begin;
	while (tmp)
	{
		next = tmp -> next;
		tmp -> destroy(tmp);
		this -> size--;
		tmp = next;
	}
	ft_free_arr(this -> arr);
	free(this);
}
