/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:45:05 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 22:50:06 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_str_arr_size(char **strarr)
{
	int	size;

	if (strarr == NULL)
		return (0);
	size = 0;
	while (strarr[size] != NULL)
		size++;
	return (size);
}

void	user_prompt(char **env_var)
{
	ft_printf("minishell ~%s $ ", ft_strnstr(ft_getenv("PWD", env_var),
			ft_getenv("HOME", env_var), ft_strlen(ft_getenv("PWD", env_var)))
		+ ft_strlen(ft_getenv("HOME", env_var)));
}
