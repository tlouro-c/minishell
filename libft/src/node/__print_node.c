/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __print_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:09:54 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/01 15:59:47 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__print_node(t_node *this, char specifier)
{
	int		i;
	char	**arr;

	if (specifier != 'i' && specifier != 'd' && specifier != 's'
		&& specifier != 'a')
	{
		ft_putstr_fd("Invalid specifier in the print function\n", 2);
		return ;
	}
	if (specifier == 'i' || specifier == 'd')
		ft_printf("%i\n", *((int *)this -> value));
	else if (specifier == 's')
		ft_printf("%s\n", (char *)this -> value);
	else 
	{
		i = 0;
		arr = (char **)this->value;
		while (arr[i])
			ft_printf("%s\n", arr[i++]);
	}
}
