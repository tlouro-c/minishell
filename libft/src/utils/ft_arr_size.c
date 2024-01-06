/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:25:30 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 16:26:05 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arr_size(void **arr)
{
	int	size;

	if (arr == NULL)
		return (0);
	size = 0;
	while (arr[size] != NULL)
		size++;
	return (size);
}
