/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:41:45 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/08 10:48:49 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	partition(char **array, int low, int high)
{
	int		pivot_index;
	char	*pivot_value;
	int		i;
	int		j;

	pivot_index = ft_rand() % (high - low + 1) + low;
	pivot_value = array[pivot_index];
	ft_swap_str(&array[pivot_index], &array[high]);
	i = low;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(array[j], pivot_value) < 0)
		{
			if (i != j)
				ft_swap_str(&array[i], &array[j]);
			i++;
		}
		j++;
	}
	ft_swap_str(&array[i], &array[high]);
	return (i);
}

static void	ft_quick_sort_recursive(char **array, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(array, low, high);
		ft_quick_sort_recursive(array, low, pivot - 1);
		ft_quick_sort_recursive(array, pivot + 1, high);
	}
}

void	ft_quick_sort_str(char **array, int size)
{
	ft_quick_sort_recursive(array, 0, size - 1);
}
