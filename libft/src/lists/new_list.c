/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:54:23 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/28 17:31:29 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*new_list(void)
{
	t_list	*new_list;

	new_list = (t_list *)ft_calloc(1, sizeof(t_list_private));
	if (!new_list)
		return (NULL);
	new_list -> add = __add;
	new_list -> print = __print;
	new_list -> destroy = __destroy;
	new_list -> toarray = __toarray;
	new_list -> removeif = __removeif;
	new_list -> set = __set;
	return (new_list);
}
