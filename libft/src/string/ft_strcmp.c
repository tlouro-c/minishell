/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:31:03 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/23 14:31:46 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL && s2 != NULL)
		return (-*s2);
	else if (s1 != NULL && s2 == NULL)
		return (*s1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
