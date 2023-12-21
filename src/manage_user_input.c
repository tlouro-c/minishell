/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:15:29 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 23:27:20 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*swap_exit_status(char *input, int last_exit_status, int index)
{
	char	*exit_status_str;
	char	*input_before_dollar;
	char	*input_after_dollar;
	char	*tmp;
	int		input_len_after_dollar;

	input_len_after_dollar = ft_strlen(input) - index - 2;
	input_before_dollar = ft_substr(input, 0, index);
	input_after_dollar = ft_substr(input, index + 2, input_len_after_dollar);
	if (input_before_dollar == NULL && input_after_dollar == NULL)
		return (NULL);
	free(input);
	exit_status_str = (char *)ft_calloc(12, sizeof(char));
	if (exit_status_str == NULL)
		return (NULL);
	exit_status_str = ft_itoa(last_exit_status, exit_status_str, 10);
	tmp = ft_strjoin(input_before_dollar, exit_status_str);
	if (tmp == NULL)
		return (NULL);
	input = ft_strjoin(tmp, input_after_dollar);
	free(tmp);
	free(exit_status_str);
	free(input_before_dollar);
	free(input_after_dollar);
	return (input);
}

static char	*swap_enviroment_variable(char *input, char **env_var, int index)
{
	char	*trimmed_input;
	char	*env_value;

	trimmed_input = ft_substr(input, 0, index);
	env_value = ft_getenv(&input[index + 1], env_var);
	free(input);
	input = ft_strjoin(trimmed_input, env_value);
	free(trimmed_input);
	return (input);
}

/*@brief
	Finds a $ sign in the input and swaps it for the 
	respective enviroment variable (it exists) or the last exit status
*/
char	*swap_env_in_input(char *input, char **env_var, int last_exit_status)
{
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				input = swap_exit_status(input, last_exit_status, i);
				if (input == NULL)
					return (NULL);
			}
			else
			{
				input = swap_enviroment_variable(input, env_var, i);
				return (input);
			}
		}
		i++;
	}
	return (input);
}
