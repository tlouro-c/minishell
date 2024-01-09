/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshrinker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:58:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/08 22:49:12 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strshrinker(char *str, char *set, int to_free)
{
	char	*new;
	int		i;
	int		j;

	if (!str || !set)
		return (NULL);
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	if (to_free)
		free(str);
	return (new);
}
