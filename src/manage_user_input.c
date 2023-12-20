/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:15:29 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 00:55:34 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
	* Finds a $ sign in the input and swaps it for the 
	respective enviroment variable (it it exists) or the last exit status
	!!! LAST EXIT STATUS PART TODO
*/
char	*swap_env_in_input(char *input, char **env_var, int last_exit_status)
{
	char	*env_value;
	char	*trimmed_input;
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		(void)last_exit_status;
		if (input[i] == '$')
		{
			trimmed_input = ft_substr(input, 0, i);
			env_value = ft_getenv(&input[i + 1], env_var);
			free(input);
			input = ft_strjoin(trimmed_input, env_value);
			free(trimmed_input);
			return (input);
		}
		i++;
	}
	return (input);
}

