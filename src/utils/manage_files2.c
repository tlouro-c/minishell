/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:35:35 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/16 13:33:16 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*exp_here_doc(char *in, t_enviroment *enviroment)
{
	t_modes	modes;
	int		i;

	modes.s_q = OFF;
	i = 0;
	while (in[i])
	{
		if (in[i] == '\'')
		{
			modes.s_q++;
			if (modes.s_q == 2)
				modes.s_q = OFF;
			i++;
		}
		else if (in[i] == '$' && modes.s_q == OFF
			&& (ft_isalphanum(in[i + 1]) || in[i + 1] == '?'))
			in = set_env_on_input(in, enviroment, &i);
		else
			i++;
	}
	return (in);
}
