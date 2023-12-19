/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:27:38 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:27:45 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_inc	increment;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	increment.written = 0;
	increment.i = 0;
	while (format[increment.i] != '\0')
	{
		if (format[increment.i] == '%')
			action(format, &args, &increment);
		else
		{
			increment.written += write (1, &format[increment.i], 1);
			increment.i++;
		}
	}
	return (increment.written);
}
