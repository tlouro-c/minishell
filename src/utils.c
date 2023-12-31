/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:45:05 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/31 13:57:48 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*path_for_prompt(t_enviroment *enviroment)
{
	char	*path;

	path = ft_getenv("PWD", enviroment->variables)
		+ ft_strlen(ft_getenv("HOME", enviroment->variables));
	return (path);
}

char	*user_prompt(t_enviroment *enviroment)
{
	char	*str_to_join[6];
	char	*prompt;
	char	*tmp;
	int		i;

	if (enviroment -> prompt != NULL)
		free(enviroment -> prompt);
	prompt = NULL;
	str_to_join[0] = "\e[1;95m";
	str_to_join[1] = ft_getenv("USER", enviroment->variables);
	str_to_join[2] = "@minishell:\e[1;96m~";
	str_to_join[3] = path_for_prompt(enviroment);
	str_to_join[4] = "$ \e[0m";
	str_to_join[5] = NULL;
	i = -1;
	while (str_to_join[++i] != NULL)
	{
		tmp = prompt;
		prompt = ft_strjoin(prompt, str_to_join[i]);
		free(tmp);
		if (prompt == NULL)
			error_allocating_memory(enviroment);
	}
	return (prompt);
}

size_t	ft_strarr_size(char **strarr)
{
	int	size;

	if (strarr == NULL)
		return (0);
	size = 0;
	while (strarr[size] != NULL)
		size++;
	return (size);
}

// void	execute_cmd(t_enviroment *enviroment)
// {
// 	//!TODO
// 	execve("path", a, enviroment->variables->arr);
// }
