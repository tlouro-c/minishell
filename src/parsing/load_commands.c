/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:00:15 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/16 15:04:58 by tlouro-c         ###   ########.fr       */
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
	cmd = mod_strdup(cmd, "\1\2\3");
	if (!cmd)
		return (NULL);
	enviroment->cmd[struct_i]->args = ft_calloc(ft_count_words(cmd, "\4")
			+ 1 + ft_isonlythis(cmd, "\4"), sizeof(char *));
	enviroment->cmd[struct_i]->delimiter = new_list();
	if (!enviroment->cmd[struct_i]->args)
	{
		free(cmd);
		return (NULL);
	}
	if (ft_isonlythis(cmd, "\4"))
	{
		free(cmd);
		enviroment->cmd[struct_i]->args[0] = ft_strdup("");
		return (enviroment->cmd[struct_i]->args);
	}
	if (split_args(cmd, enviroment, struct_i) == NULL)
		error_allocating_memory(enviroment);
	free(cmd);
	return (enviroment->cmd[struct_i]->args);
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
			enviroment->cmd[j]->has_input_file = enviroment->cmd[j]->input_file
				|| enviroment->cmd[j]->delimiter->begin;
			enviroment->cmd[j]->has_output_file
				= enviroment->cmd[j]->output_file
				|| enviroment->cmd[j]->append_file;
			j++;
		}
		i++;
	}
}

int	load_commands(t_enviroment *enviroment, char *in)
{
	int	i;

	enviroment->parsing_error = FALSE;
	in = phase1(in, enviroment);
	if (enviroment->parsing_error)
		return (msg_parsing_error(in, enviroment));
	in = phase2(in, enviroment);
	enviroment->num_cmd = ft_count_words(in, "\1\2\3");
	enviroment->cmd = ft_calloc(enviroment->num_cmd + 1, sizeof(t_cmd *));
	if (!enviroment->cmd)
		error_allocating_memory_free_str(enviroment, in);
	i = 0;
	while (i < (int)enviroment->num_cmd)
	{
		enviroment->cmd[i] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		if (!enviroment->cmd[i])
			error_allocating_memory_free_str(enviroment, in);
		enviroment->cmd[i]->prio = RED;
		enviroment->cmd[i++]->valid = 0;
	}
	split_commands(enviroment, in, "\1\2\3");
	free(in);
	pathfinder(enviroment);
	return (0);
}

int	ft_parsing_error(char *s)
{
	int		i;
	char	last_c;

	last_c = 0;
	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		if (s[i] == SPACE)
			i--;
		else
		{
			last_c = s[i];
			break ;
		}
	}
	if (last_c == OR || last_c == PIPE || last_c == AND || last_c == RED_LEFT
		|| last_c == RED_RIGHT)
		return (1);
	return (0);
}
