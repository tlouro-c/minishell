/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:11:00 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:24:18 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_x(t_flags_x flags, unsigned long n);
static void	initialize_flags(t_flags_x *flags, char specifier);
static int	write_number(unsigned long n, t_flags_x flags);
static int	get_flag_track_usage(unsigned long n, t_flags_x flags);

int	apply_x(const char *format, va_list *args, int pos, char specifier)
{
	t_flags_x			flags;
	unsigned long		n;

	initialize_flags(&flags, specifier);
	n = (unsigned long)va_arg(*args, unsigned int);
	while (format[pos] != '\0' && isflag(format[pos]))
	{
		if (format[pos] == '-')
			flags.hifen = TRUE;
		if (format[pos] == '0')
			flags.zero = TRUE;
		if (format[pos] == '#')
			flags.hash = TRUE;
		pos++;
	}
	flags.width = ft_atoi(&format[pos]);
	while (format[pos] != '\0' && ft_isdigit(format[pos]))
		pos++;
	if (format[pos] == '.')
	{
		flags.precision_on = TRUE;
		flags.precision = ft_atoi(&format[++pos]);
	}
	return (write_x(flags, n));
}

static int	write_x(t_flags_x flags, unsigned long n)
{
	int		written;
	int		track_flag_usage;

	written = 0;
	track_flag_usage = get_flag_track_usage(n, flags);
	if (flags.hifen)
	{
		written += write_number(n, flags);
		written += write_c_x_times(' ', flags.width - track_flag_usage);
	}
	else
	{
		if ((flags.zero == TRUE && n != 0) && ((flags.precision_on == FALSE)
				|| (flags.width > track_flag_usage && flags.precision == 0)))
			written += write_c_x_times('0', flags.width - track_flag_usage);
		else
			written += write_c_x_times(' ', flags.width - track_flag_usage);
		written += write_number(n, flags);
	}
	return (written);
}

static int	write_number(unsigned long n, t_flags_x flags)
{
	int	written;
	int	zeros;

	written = 0;
	zeros = flags.precision - hexa_len(n, 16, "0123456789abcdef");
	if (flags.hash == TRUE && flags.upper_case == FALSE && n != 0)
		written += write(1, "0x", 2);
	else if (flags.hash == TRUE && flags.upper_case == TRUE && n != 0)
		written += write(1, "0X", 2);
	if (flags.precision && zeros > 0)
		written += write_c_x_times('0', zeros);
	if (flags.upper_case == FALSE 
		&& (!(n == 0 && flags.precision_on == TRUE && flags.precision == 0)))
		written += ft_putnbr_bases(n, 16, "0123456789abcdef");
	else if ((!(n == 0 && flags.precision_on == TRUE && flags.precision == 0)))
		written += ft_putnbr_bases(n, 16, "0123456789ABCDEF");
	return (written);
}

static void	initialize_flags(t_flags_x *flags, char specifier)
{
	flags -> precision = 0;
	flags -> hifen = FALSE;
	flags -> zero = FALSE;
	flags -> hash = FALSE;
	flags -> upper_case = specifier == 'X';
}

static int	get_flag_track_usage(unsigned long n, t_flags_x flags)
{
	int	track_flag_usage;

	track_flag_usage = 0;
	if (flags.hash)
		track_flag_usage += 2;
	if (flags.precision > hexa_len(n, 16, "0123456789abcdef"))
		track_flag_usage += flags.precision;
	else
		track_flag_usage += hexa_len(n, 16, "0123456789abcdef")
			- (flags.precision_on == TRUE && flags.precision == 0 && n == 0);
	return (track_flag_usage);
}
