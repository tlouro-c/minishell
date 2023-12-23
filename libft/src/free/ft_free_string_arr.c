/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_string_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:52:34 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/23 12:54:54 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_str_arr(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(array[i++]);
	free(array);
	return (NULL);
}
