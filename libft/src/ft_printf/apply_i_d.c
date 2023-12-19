/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_i_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:56:21 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:24:10 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_i_d(t_flags_i_d flags, int n);
static void	initialize_flags(t_flags_i_d *flags);
static int	write_number(int n, t_flags_i_d flags, int track_flag_usage);
static int	edge_case_check_and_print(int n, t_flags_i_d flags,
				int track_flag_usage, int zeros);

int	apply_i_d(const char *format, va_list *args, int pos)
{
	t_flags_i_d	flags;

	initialize_flags(&flags);
	while (format[pos] != '\0' && isflag(format[pos]))
	{
		if (format[pos] == '-')
			flags.hifen = TRUE;
		if (format[pos] == '0')
			flags.zero = TRUE;
		if (format[pos] == '+')
			flags.plus = TRUE;
		if (format[pos] == ' ')
			flags.space = TRUE;
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
	return (write_i_d(flags, va_arg(*args, int)));
}

static int	write_i_d(t_flags_i_d flags, int n)
{
	int		written;
	int		track_flag_usage;

	written = 0;
	track_flag_usage = 0;
	if (flags.plus || flags.space || n < 0)
		track_flag_usage += 1;
	if (flags.precision_on && flags.precision >= number_len(n))
		track_flag_usage += flags.precision;
	else
		track_flag_usage += number_len(n)
			- (n == 0 && flags.precision_on == TRUE && flags.precision == 0);
	if (flags.plus && n >= 0)
		written += write(1, "+", 1);
	else if (flags.space && n >= 0)
		written += write(1, " ", 1);
	else if (n < 0 && (flags.width <= track_flag_usage
			|| (flags.zero == TRUE && flags.precision_on == FALSE)
			|| flags.hifen))
	{
		written += write(1, "-", 1);
		flags.written_minus = TRUE;
	}
	written += write_number(n, flags, track_flag_usage);
	return (written);
}

static int	write_number(int n, t_flags_i_d flags, int track_flag_usage)
{
	int	written;
	int	zeros;

	written = 0;
	zeros = flags.precision - number_len(n);
	if (flags.hifen)
	{
		if (flags.precision && zeros > 0)
			written += write_c_x_times('0', zeros);
		written += edge_case_check_and_print(n, flags, track_flag_usage, zeros);
		written += write_c_x_times(' ', flags.width - track_flag_usage);
	}
	else
	{
		if (flags.zero == TRUE && flags.precision_on == FALSE)
			written += write_c_x_times('0', flags.width - track_flag_usage);
		else
			written += write_c_x_times(' ', flags.width - track_flag_usage);
		if (quick_edge(n, flags))
			written += write(1, "-", 1);
		if (flags.precision && zeros > 0)
			written += write_c_x_times('0', zeros);
		written += edge_case_check_and_print(n, flags, track_flag_usage, zeros);
	}
	return (written);
}

static void	initialize_flags(t_flags_i_d *flags)
{
	flags -> written_minus = FALSE;
	flags -> width = 0;
	flags -> precision_on = FALSE;
	flags -> precision = 0;
	flags -> hifen = FALSE;
	flags -> zero = FALSE;
	flags -> plus = FALSE;
	flags -> space = FALSE;
}

static int	edge_case_check_and_print(int n, t_flags_i_d flags,
				int track_flag_usage, int zeros)
{
	int	written;

	written = 0;
	if (flags.precision == 0 && flags.precision_on == TRUE && n == 0)
		return (0);
	if (flags.width > track_flag_usage && n < 0 && zeros <= 0
		&& flags.zero == FALSE && flags.written_minus == FALSE)
		written += write (1, "-", 1);
	putnbr_d_i((long)n);
	written += number_len(n);
	return (written);
}
