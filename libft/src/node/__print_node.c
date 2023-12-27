/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __print_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:09:54 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 16:15:43 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__print_node(t_node *this, char specifier)
{
	if (specifier != 'i' && specifier != 'd' && specifier != 's')
	{
		ft_putstr_fd("Invalid specifier in the print function\n", 2);
		return ;
	}
	if (specifier == 'i' || specifier == 'd')
		ft_printf("%i\n", (int *)this -> value);
	else 
		ft_printf("%s\n", (char *)this -> value);
}
