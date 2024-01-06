/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:57:37 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 12:15:44 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	action(const char *format, va_list *args, t_inc *increment)
{
	char	specifier;
	int		return_value;
	int		pos;

	pos = increment -> i + 1;
	specifier = find_specifier(format, increment);
	if (specifier == 'c')
		increment -> written += apply_c(format, args, pos);
	else if (specifier == 's')
	{
		return_value = apply_s(format, args, pos);
		if (return_value == -1)
			alloc_error_exit(2, args);
		increment -> written += return_value;
	}
	else if (specifier == 'p')
		increment -> written += apply_p(format, args, pos);
	else if (specifier == 'i' || specifier == 'd')
		increment -> written += apply_i_d(format, args, pos);
	else if (specifier == 'u')
		increment -> written += apply_u(format, args, pos);
	else if (specifier == 'X' || specifier == 'x')
		increment -> written += apply_x(format, args, pos, specifier);
	else
		increment -> written += invalid_specifier_or_special(specifier, args);
}

char	find_specifier(const char *format, t_inc *increment)
{
	increment -> i++;
	while (format[increment->i] != '\0' && isflag(format[increment->i]))
		increment->i++;
	while (format[increment->i] != '\0' && ft_isdigit(format[increment->i]))
		increment->i++;
	if (format[increment->i] == '.')
	{
		increment->i++;
		while (format[increment->i] != '\0'
			&& ft_isdigit(format[increment->i]))
			increment->i++;
	}
	if (format[increment->i] != '\0')
		increment->i++;
	return (format[increment->i - 1]);
}

t_bool	isflag(char c)
{
	return (c == '-' || c == ' ' || c == '0' || c == '#' || c == '+');
}

int	write_c_x_times(char c, int x)
{
	int	i;

	if (x < 0)
		return (0);
	i = 0;
	while (i < x)
	{
		write (1, &c, 1);
		i++;
	}
	return (x);
}

void	alloc_error_exit(int error_value, va_list *args)
{
	va_end(*args);
	ft_putstr_fd("Error: Memory allocation failed.", 2);
	exit (error_value);
}
