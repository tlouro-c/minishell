/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:32:16 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 16:12:26 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__print(t_list *this, char specifier)
{
	t_node	*tmp;

	tmp = this -> begin;
	while (tmp)
	{
		tmp -> print(tmp, specifier);
		tmp = tmp -> next;
	}
}
