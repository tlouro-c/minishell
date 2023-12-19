/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:51:36 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:24:14 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*tmp_strcut(char *s, int start_len, int final_len);
static void	assign_string(char **s, va_list *args);
static void	initialize_flags(t_flags_s *flags);
static int	write_s(t_flags_s flags, char *s);

int	apply_s(const char *format, va_list *args, int pos)
{
	t_flags_s	flags;
	char		*s;

	initialize_flags(&flags);
	assign_string(&s, args);
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
		if ((ft_strcmp(s, "(null)") == 0) && flags.precision <= 5)
			flags.precision = 0;
	}
	return (write_s(flags, s));
}

static int	write_s(t_flags_s flags, char *s)
{
	char	*print;
	int		written;
	int		str_len;

	str_len = ft_strlen(s);
	written = 0;
	print = tmp_strcut(ft_strdup(s), str_len, flags.precision);
	if (print == NULL)
		return (-1);
	if (flags.hifen)
	{
		written += ft_putstr_fd(print, 1);
		written += write_c_x_times(' ', flags.width - ft_strlen(print));
	}
	else
	{
		if (flags.zero && ft_strcmp(s, "(null)") != 0)
			written += write_c_x_times('0', flags.width - ft_strlen(print));
		else
			written += write_c_x_times(' ', flags.width - ft_strlen(print));
		written += ft_putstr_fd(print, 1);
	}
	free(print);
	return (written);
}

static void	initialize_flags(t_flags_s *flags)
{
	flags -> width = 0;
	flags -> precision = INT_MAX;
	flags -> precision_on = FALSE;
	flags -> hifen = FALSE;
	flags -> zero = FALSE;
}

static void	assign_string(char **s, va_list *args)
{
	*s = va_arg(*args, char *);
	if (*s == NULL)
		*s = "(null)";
}

static char	*tmp_strcut(char *s, int start_len, int final_len)
{
	int	to_cut;
	int	i;

	if (s == NULL)
		return (NULL);
	if (final_len > start_len)
		to_cut = 0;
	else
		to_cut = ft_abs(final_len - start_len);
	i = 0;
	while (i < to_cut)
	{
		s[start_len - 1] = '\0';
		start_len--;
		i++;
	}
	return (s);
}
