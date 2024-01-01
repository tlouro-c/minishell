/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:12:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/01 20:41:58 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*mod_strdup(char const *s, char *sep)
{
	char	*s2;
	int		i;

	i = 0;
	while (!ft_isinstr(sep, s[i]) && s[i] != '\0')
		i++;
	s2 = ft_calloc((i + 1), sizeof(char));
	if (!s2)
		return (s2);
	i = 0;
	while (!ft_isinstr(sep, s[i]) && s[i] != '\0')
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**ft_split(char const *s, char *sep)
{
	char	**sarray;
	int		j;
	int		i;

	sarray = ft_calloc((ft_count_words(s, sep) + 1), sizeof(char *));
	if (!sarray)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && !ft_isinstr(sep, s[0]) && s[0] != '\0')
			|| (i > 0 && !ft_isinstr(sep, s[i]) && ft_isinstr(sep, s[i - 1])))
		{
			sarray[j] = mod_strdup(&s[i], sep);
			if (!sarray[j])
				return ((char **)ft_free_arr((void **)sarray));
			j++;
		}
		i++;
	}
	sarray[j] = NULL;
	return (sarray);
}
