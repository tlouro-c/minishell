/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:15:29 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/28 01:04:26 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	mem_error_here(t_enviroment *enviroment, char **input, char **optional)
{
	if (*optional)
		free(*optional);
	free(*input);
	error_allocating_memory(enviroment);
}

static char	*ft_strjoin3(char **s1, char *local, char **s3)
{
	char	*final;
	char	*tmp;

	tmp = ft_strjoin(*s1, local);
	final = ft_strjoin(tmp, *s3);
	free(*s1);
	free(*s3);
	if (!tmp || !final)
	{
		if (tmp)
			free(tmp);
		if (final)
			free(final);
		return (NULL);
	}
	free(tmp);
	return (final);
}

static char	*swap_exit_status(char **input, t_enviroment *enviroment, int index)
{
	char	exit_status[12];
	char	*input_before;
	char	*input_after;

	ft_itoa(enviroment->last_exit_status, exit_status, 10);
	input_before = ft_substr(*input, 0, index);
	if (!input_before)
		mem_error_here(enviroment, input, NULL);
	input_after = ft_substr(*input, index + 2, ft_strlen(*input) - index - 2);
	if (input_after == NULL)
		mem_error_here(enviroment, input, &input_before);
	free(*input);
	*input = ft_strjoin3(&input_before, exit_status, &input_after);
	if (!input)
		mem_error_here(enviroment, input, NULL);
	return (*input);
}

static char	*swap_enviroment_variable(char **input, t_enviroment *enviroment, int index)
{
	char	*input_before_dollar;
	char	*input_after_dollar;
	char	*env_value;

	input_before_dollar = ft_substr(*input, 0, index);
	if (!input_before_dollar)
		mem_error_here(enviroment, input, NULL);
	env_value = ft_getenv(&(*input)[index + 1], enviroment->variables);
	while (ft_isalpha((*input)[++index]))
	input_after_dollar = ft_substr(*input, index, ft_strlen(*input) - index);
	if (!input_after_dollar)
		mem_error_here(enviroment, input, &input_before_dollar);
	free(*input);
	*input = ft_strjoin3(&input_before_dollar, env_value, &input_after_dollar);
	return (*input);
}

/*@brief
	Finds a $ sign in the input and swaps it for the 
	respective enviroment variable (it exists) or the last exit status
*/
char	*swap_env_in_input(char **input, t_enviroment *enviroment)
{
	int		i;
	int		single_quote_mode;

	i = 0;
	single_quote_mode = 0;
	while ((*input)[i] != '\0')
	{
		if ((*input)[i] == '\'')
			single_quote_mode++;
		if (single_quote_mode == 2)
			single_quote_mode = 0;
		if ((*input)[i] == '$' && (*input)[i] != '\0' && !single_quote_mode)
		{
			if ((*input)[i + 1] == '?')
				*input = swap_exit_status(input, enviroment, i);
			else
				*input = swap_enviroment_variable(input, enviroment, i);
		}
		i++;
	}
	return (*input);
}
