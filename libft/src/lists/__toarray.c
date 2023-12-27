/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __toarray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:54:28 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 00:21:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**__toarray(t_list *this)
{
	void	**arr;
	t_node	*tmp;
	int		i;

	if (((t_list_private *)this)-> needs_update == 0)
		return (((t_list_private *)this)-> arr);
	free(((t_list_private *)this)-> arr);
	arr = (void **)ft_calloc(this -> size + 1, sizeof(void *));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = this -> begin;
	while (tmp)
	{
		arr[i++] = tmp -> value;
		tmp = tmp -> next;
	}
	((t_list_private *)this)-> needs_update = 0;
	((t_list_private *)this)-> arr = arr;
	return (arr);
}
