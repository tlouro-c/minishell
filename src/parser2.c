/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:00:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 19:54:49 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	manage_priorities(char *in, int index)
{
	int	priorities;

	if (index == 0)
		priorities = PIPE;
	else
		priorities = in[index - 1];
	return (priorities);
}

static char	**manage_args(char *cmd, t_enviroment *enviroment, int struct_i)
{
	char **temp;
	
	cmd = mod_strdup(cmd, "\1\2\3");
	if (!cmd)
		return (NULL);
	enviroment->cmd[struct_i]->args = ft_calloc(ft_count_words(cmd, "\4\5\6") + 1,
			sizeof(char *));
	if (!enviroment->cmd[struct_i]->args)
	{
		free(cmd);
		return (NULL);
	}
	temp = split_args(cmd, enviroment, struct_i);
	free(cmd);
	return (temp);
}

static void	split_commands(t_enviroment *enviroment, char *in, char *sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (in[i])
	{
		if ((i == 0 && !ft_isinstr(sep, in[i]) && in[i] != '\0')
			|| (!ft_isinstr(sep, in[i]) && ft_isinstr(sep, in[i - 1])))
		{
			enviroment -> cmd[j]-> priorities = manage_priorities(in, i);
			enviroment -> cmd[j]-> args = manage_args(&in[i], enviroment, j);
			if (enviroment -> cmd[j]-> args == NULL)
				error_allocating_memory_free_str(enviroment, in);
			j++;
		}
		i++;
	}
}

void	load_commands(t_enviroment *enviroment, char *in)
{
	int	i;

	in = phase1(in);
	in = phase2(in, enviroment);
	enviroment->num_cmd = ft_count_words(in, "\1\2\3");
	enviroment->cmd = (t_cmd **)ft_calloc(enviroment->num_cmd + 1,
			sizeof(t_cmd *));
	if (!enviroment->cmd)
		error_allocating_memory_free_str(enviroment, in);
	i = 0;
	while (i < (int)enviroment->num_cmd)
	{
		enviroment->cmd[i] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		if (!enviroment->cmd[i])
			error_allocating_memory_free_str(enviroment, in);
		i++;
	}
	split_commands(enviroment, in, "\1\2\3");
	free(in);
	pathfinder(enviroment);
}
