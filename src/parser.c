/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 00:15:29 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/31 14:01:08 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	manage_mode(char c, t_modes *modes)
{
	if (c == '\'' && modes -> d_q == OFF)
		modes -> s_q++;
	else if (c == '"' && modes -> s_q == OFF)
		modes -> d_q++;
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
		ft_itoa(enviroment->last_exit_status, exit, 10);
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
		manage_mode(in[i], &modes);
		if (in[i] == '$' && (ft_isalphanum(in[i + 1]) || in[i + 1] == '?')
			&& modes.s_q == OFF)
			in = set_env_on_input(in, enviroment, &i);
		else
			i++;
	}
	return (in);
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
		manage_mode(in[i], &modes);
		if (in[i] == '|' && modes.d_q == OFF && modes.s_q == OFF)
			in[i] = '\1';
		else if (in[i] == ' ' && modes.d_q == OFF && modes.s_q == OFF)
			in[i] = '\2';
		i++;
	}
	return (in);
}
