/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:15:29 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 23:49:22 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	manage_mode(char *c, t_modes *modes)
{
	if ((*c == '\'' || *c == S_QUOTE) && modes->d_q == OFF)
	{
		modes -> s_q++;
		*c = S_QUOTE;
	}
	else if ((*c == '"' || *c == D_QUOTE) && modes->s_q == OFF)
	{
		modes -> d_q++;
		*c = D_QUOTE;
	}
	if (modes -> s_q == 2)
		modes -> s_q = OFF;
	else if (modes -> d_q == 2)
		modes -> d_q = OFF;
}

static char	*set_env_on_input(char *in, t_enviroment *enviroment, int *i)
{
	char	exit[12];
	char	*before;
	char	*middle;
	char	*after;
	char	*tmp;

	if (in[*i + 1] == '?')
	{
		ft_itoa(enviroment->status, exit, 10);
		middle = exit;
	}
	else
		middle = ft_getenv(&in[*i + 1], enviroment->variables);
	before = ft_substr(in, 0, *i);
	if (!before)
		error_allocating_memory(enviroment);
	after = &in[*i + ft_keylen(&in[*i + 1]) + 1 + (in[*i + 1] == '?')];
	tmp = ft_strjoin_3(before, middle, after);
	free(in);
	free(before);
	if (!tmp)
		error_allocating_memory(enviroment);
	in = tmp;
	*i += ft_strlen(middle);
	return (in);
}

char	*phase2(char *in, t_enviroment *enviroment)
{
	t_modes	modes;
	int		i;

	modes.d_q = OFF;
	modes.s_q = OFF;
	i = 0;
	while (in[i])
	{
		manage_mode(&in[i], &modes);
		if (in[i] == '$' && modes.s_q == OFF
			&& (ft_isalphanum(in[i + 1]) || in[i + 1] == '?'))
			in = set_env_on_input(in, enviroment, &i);
		else
			i++;
	}
	return (in);
}

static void	manage_command_separators(char *c, t_modes *modes)
{
	if (*c == '|' && *(c + 1) == '|' && modes->d_q == OFF && modes->s_q == OFF)
	{
		*c = OR;
		*(c + 1) = OR;
	}
	else if (*c == '|' && modes->d_q == OFF && modes->s_q == OFF)
		*c = PIPE;
	else if (*c == '&' && *(c + 1) == '&'
		&& modes->d_q == OFF && modes->s_q == OFF)
	{
		*c = AND;
		*(c + 1) = AND;
	}
}

char	*phase1(char *in)
{
	t_modes	modes;
	int		i;

	modes.d_q = OFF;
	modes.s_q = OFF;
	i = 0;
	while (in[i])
	{
		if (in[i] == '"' || in[i] == '\'')
			manage_mode(&in[i], &modes);
		if ((in[i] == '|' || in[i] == '&')
			&& modes.d_q == OFF && modes.s_q == OFF)
			manage_command_separators(&in[i], &modes);
		else if (in[i] == ' ' && modes.d_q == OFF && modes.s_q == OFF)
			in[i] = SPACE;
		i++;
	}
	return (in);
}
