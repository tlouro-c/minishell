/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:34:10 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:24:16 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_u(t_flags_u flags, unsigned int n);
static void	initialize_flags(t_flags_u *flags);
static int	write_number(unsigned int n, t_flags_u flags);
static void	putnbr_u(unsigned int n);

int	apply_u(const char *format, va_list *args, int pos)
{
	t_flags_u	flags;

	initialize_flags(&flags);
	while (format[pos] != '\0' && isflag(format[pos]))
	{
		if (format[pos] == '-')
			flags.hifen = TRUE;
		if (format[pos] == '0')
			flags.zero = TRUE;
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
	return (write_u(flags, (unsigned int)va_arg(*args, int)));
}

static int	write_u(t_flags_u flags, unsigned int n)
{
	int		written;
	int		track_flag_usage;

	written = 0;
	track_flag_usage = 0;
	if (flags.precision > number_len_u(n))
		track_flag_usage += flags.precision;
	else
		track_flag_usage += number_len_u(n) - (n == 0
				&& flags.precision_on == TRUE && flags.precision == 0);
	if (flags.hifen)
	{
		written += write_number(n, flags);
		written += write_c_x_times(' ', flags.width - track_flag_usage);
	}
	else
	{
		if (flags.zero == TRUE && flags.precision_on == FALSE)
			written += write_c_x_times('0', flags.width - track_flag_usage);
		else
			written += write_c_x_times(' ', flags.width - track_flag_usage);
		written += write_number(n, flags);
	}
	return (written);
}

static int	write_number(unsigned int n, t_flags_u flags)
{
	int	written;
	int	zeros;

	written = 0;
	zeros = flags.precision - number_len_u(n);
	if (flags.precision && zeros > 0)
		written += write_c_x_times('0', zeros);
	if (!(n == 0 && flags.precision_on == TRUE && flags.precision == 0))
		putnbr_u(n);
	written += number_len_u(n) - (n == 0 && flags.precision_on == TRUE 
			&& flags.precision == 0);
	return (written);
}

static void	initialize_flags(t_flags_u *flags)
{
	flags -> width = 0;
	flags -> precision_on = FALSE;
	flags -> precision = 0;
	flags -> hifen = FALSE;
	flags -> zero = FALSE;
}

static void	putnbr_u(unsigned int n)
{
	char	toprint;

	if (n >= 10)
		putnbr_u(n / 10);
	toprint = (n % 10) + 48;
	write(1, &toprint, 1);
}
