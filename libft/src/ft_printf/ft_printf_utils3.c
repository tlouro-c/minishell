/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:51:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:30:29 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	invalid_specifier_or_special(char specifier, va_list *args)
{
	if (specifier == '%')
		return (write(1, "%", 1));
	va_end(*args);
	ft_putstr_fd("Error: Invalid conversion specifier '", 2);
	ft_putchar_fd(specifier, 2);
	ft_putstr_fd("'\n", 2);
	exit(3);
}

void	putnbr_d_i(long n)
{
	char	toprint;

	if (n < 0)
		n = n * -1;
	if (n >= 10)
		putnbr_d_i(n / 10);
	toprint = (n % 10) + 48;
	write(1, &toprint, 1);
}

int	number_len_u(unsigned int number)
{
	int	number_len;

	number_len = number == 0;
	while (number > 0)
	{
		number = number / 10;
		number_len++;
	}
	return (number_len);
}
