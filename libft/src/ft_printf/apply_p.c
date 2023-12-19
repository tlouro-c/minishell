/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:40:04 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:24:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_p(t_flags_c_p flags, unsigned long p);
static int	nil(t_flags_c_p flags, char *s);
static int	ox_zero(t_flags_c_p flags, unsigned long p);
static int	space_ox(t_flags_c_p flags, unsigned long p);

int	apply_p(const char *format, va_list *args, int pos)
{
	t_flags_c_p			flags;
	unsigned long		p;

	flags.hifen = FALSE;
	flags.zero = FALSE;
	p = (unsigned long)va_arg(*args, void *);
	while (format[pos] != '\0' && isflag(format[pos]))
	{
		if (format[pos] == '-')
			flags.hifen = TRUE;
		if (format[pos] == '0')
			flags.zero = TRUE;
		pos++;
	}
	flags.width = ft_atoi(&format[pos]);
	return (write_p(flags, p));
}

static int	write_p(t_flags_c_p flags, unsigned long p)
{
	int		written;

	written = 0;
	if (p == 0)
		written += nil(flags, "(nil)");
	else
	{
		if (flags.hifen)
		{
			written += write (1, "0x", 2);
			written += ft_putnbr_bases(p, 16, "0123456789abcdef");
			written += write_c_x_times(' ', flags.width - (2
						+ hexa_len(p, 16, "0123456789abcdef")));
		}
		else
		{
			if (flags.zero)
				written += ox_zero(flags, p);
			else
				written += space_ox(flags, p);
			written += ft_putnbr_bases(p, 16, "0123456789abcdef");
		}
	}
	return (written);
}

static int	nil(t_flags_c_p flags, char *s)
{
	int		written;

	written = 0;
	if (flags.hifen)
	{
		written += ft_putstr_fd(s, 1);
		written += write_c_x_times(' ', flags.width - ft_strlen(s));
	}
	else
	{
		if (flags.zero)
			written += write_c_x_times('0', flags.width - ft_strlen(s));
		else
			written += write_c_x_times(' ', flags.width - ft_strlen(s));
		written += ft_putstr_fd(s, 1);
	}
	return (written);
}

static int	ox_zero(t_flags_c_p flags, unsigned long p)
{
	int	written;

	written = 0;
	written += write (1, "0x", 2);
	written += write_c_x_times('0', flags.width - (2
				+ hexa_len(p, 16, "0123456789abcdef")));
	return (written);
}

static int	space_ox(t_flags_c_p flags, unsigned long p)
{
	int	written;

	written = 0;
	written += write_c_x_times(' ', flags.width - (2
				+ hexa_len(p, 16, "0123456789abcdef")));
	written += write (1, "0x", 2);
	return (written);
}
