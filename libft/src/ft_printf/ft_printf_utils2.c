/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:52:49 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:24:23 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_bases_rec(unsigned long n, int base_size,
		char *base, int	*counter)
{
	char	toprint;

	if (n >= (unsigned long)base_size)
		ft_putnbr_bases_rec(n / (unsigned long)base_size, base_size, base,
			counter);
	toprint = base[n % base_size];
	*counter = (*counter) + write(1, &toprint, 1);
}

int	ft_putnbr_bases(unsigned long n, int base_size, char *base)
{
	int	counter;

	counter = 0;
	ft_putnbr_bases_rec(n, base_size, base, &counter);
	return (counter);
}

int	number_len(int number)
{
	int	number_len;

	number_len = number == 0;
	if (number == INT_MIN)
		number++;
	if (number < 0)
		number = number * -1;
	while (number > 0)
	{
		number = number / 10;
		number_len++;
	}
	return (number_len);
}

static void	hexa_len_rec(unsigned long n, int base_size, char *base, int *i)
{
	if (n >= (unsigned long)base_size)
		hexa_len_rec(n / (unsigned long)base_size, base_size, base, i);
	*i = *i + 1;
}

int	hexa_len(unsigned long n, int base_size, char *base)
{
	int	counter;

	counter = 0;
	hexa_len_rec(n, base_size, base, &counter);
	return (counter);
}
