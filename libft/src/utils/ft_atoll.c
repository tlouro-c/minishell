/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:01:09 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 17:06:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *s)
{
	long long	n;
	int			i;
	int			negative;

	if (s == NULL)
		return (0);
	n = 0;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	negative = s[i] == '-';
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] != '\0' && ft_isdigit(s[i]))
		n = n * 10 + (s[i++] - '0');
	if (negative)
		return (n * -1);
	return (n);
}
