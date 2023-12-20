/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:45:05 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 23:16:22 by tlouro-c         ###   ########.fr       */
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

char	*user_prompt(char **env_var)
{
	char	*str_to_join[6];
	char	*prompt;
	char	*tmp;
	int		i;

	prompt = NULL;
	str_to_join[0] = "\e[1;95m";
	str_to_join[1] = ft_getenv("USER", env_var);
	str_to_join[2] = "@minishell:\e[1;96m~";
	str_to_join[3] = ft_strnstr(ft_getenv("PWD", env_var),
			ft_getenv("HOME", env_var), ft_strlen(ft_getenv("PWD", env_var)));
	str_to_join[4] = "$ \e[0m";
	str_to_join[5] = NULL;
	i = -1;
	while (str_to_join[++i] != NULL)
	{
		tmp = prompt;
		prompt = ft_strjoin(prompt, str_to_join[i]);
		free(tmp);
		if (prompt == NULL)
		{
			ft_free_str_arr(env_var, ft_str_arr_size(env_var));
			error_allocating_memory();
		}
	}
	return (prompt);
}
