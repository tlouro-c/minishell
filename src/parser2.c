/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:00:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/02 14:25:57 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


static void	split_commands(t_enviroment *enviroment, char *in)
{
	t_cmd	**cmd_arr;
	int	i;

	i = 0;
}

void	load_commands(t_enviroment *enviroment, char *in)
{
	enviroment->cmd = new_list();
	in = phase1(in);
	in = phase2(in, enviroment);
	split_commands(enviroment, in);
	int	i;
	i = 0;
	while (in[i])
	{
		if (in[i] == PIPE || in[i] == OR)
			ft_printf("|");
		else if (in[i] == AND)
			ft_printf("&");
		else if (in[i] == SPACE)
			ft_printf(" ");
		else
			ft_printf("%c", in[i]);
		i++;
	}
	ft_printf("\n");
}
