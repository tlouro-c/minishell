/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:38:30 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:24:04 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_c(t_flags_c_p flags, char c);

int	apply_c(const char *format, va_list *args, int pos)
{
	t_flags_c_p	flags;
	char		c;

	flags.hifen = FALSE;
	flags.zero = FALSE;
	c = (char)va_arg(*args, int);
	while (format[pos] != '\0' && isflag(format[pos]))
	{
		if (format[pos] == '-')
			flags.hifen = TRUE;
		if (format[pos] == '0')
			flags.zero = TRUE;
		pos++;
	}
	flags.width = ft_atoi(&format[pos]);
	return (write_c(flags, c));
}

static int	write_c(t_flags_c_p flags, char c)
{
	int		written;

	written = 0;
	if (flags.hifen)
	{
		written += write (1, &c, 1);
		written += write_c_x_times(' ', flags.width - 1);
	}
	else
	{
		if (flags.zero)
			written += write_c_x_times('0', flags.width - 1);
		else
			written += write_c_x_times(' ', flags.width - 1);
		written += write (1, &c, 1);
	}
	return (written);
}
