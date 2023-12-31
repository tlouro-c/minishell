/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:07:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/01 20:34:09 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char *sep)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (s[i] == '\0')
		return (counter);
	if (!ft_isinstr(sep, s[i]))
		counter++;
	i++;
	while (s[i] != '\0')
	{
		if (!ft_isinstr(sep, s[i]) && ft_isinstr(sep, s[i - 1]))
			counter++;
		i++;
	}
	return (counter);
}
