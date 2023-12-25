/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:54:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/25 01:10:42 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_getkey(char *buffer, char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		buffer[i] = s[i];
		i++;
	}
	return (buffer);
}
