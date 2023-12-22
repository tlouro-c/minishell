/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:54:17 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 13:26:39 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_node *list, char format_specifier)
{
	t_node	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (format_specifier == 'i' || format_specifier == 'd')
			ft_printf("%i\n", tmp->content);
		else if (format_specifier == 's')
			ft_printf("%s\n", tmp->content);
		tmp = tmp -> next;
	}
}
