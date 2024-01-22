/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:23:28 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/22 19:05:29 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	free_and_reassign(t_cmd *cmd, char *new_str, int prio)
{
	if (prio == RED)
	{
		free(cmd->input_file);
		new_str = ft_strshrinker(new_str, "\e\a\5\6", 1);
		cmd->input_file = new_str;
	}
	else if (prio == APP)
	{
		free(cmd->append_file);
		new_str = ft_strshrinker(new_str, "\e\a\5\6", 1);
		cmd->append_file = new_str;
		cmd->prio = APP;
	}
	else if (prio == OVE)
	{
		free(cmd->output_file);
		new_str = ft_strshrinker(new_str, "\e\a\5\6", 1);
		cmd->output_file = new_str;
		cmd->prio = OVE;
	}
}

static int	manage_redirections(char *s, t_enviroment *enviroment,
				int struct_i, int *string_i)
{
	int		st;
	int		nd;
	char	*f_o_d;

	st = s[*string_i];
	nd = s[*string_i + 1];
	while (s[*string_i] == '\4' || s[*string_i] == RED_LEFT
		|| s[*string_i] == RED_RIGHT)
		(*string_i)++;
	f_o_d = mod_strdup(&s[*string_i], "\4\14\15");
	(*string_i) += ft_strlen(f_o_d);
	if (!f_o_d)
		return (-1);
	if (st == RED_LEFT && nd == RED_LEFT)
		enviroment->cmd[struct_i]->delimiter->add(
			enviroment->cmd[struct_i]->delimiter, f_o_d);
	else if (st == RED_LEFT)
		free_and_reassign(enviroment->cmd[struct_i], f_o_d, RED);
	else if (st == RED_RIGHT && nd == RED_RIGHT)
		free_and_reassign(enviroment->cmd[struct_i], f_o_d, APP);
	else if (st == RED_RIGHT)
		free_and_reassign(enviroment->cmd[struct_i], f_o_d, OVE);
	return (1);
}

static int	create_arg(t_cmd *cmd, char *s, int *i, int j)
{
	cmd->args[j] = mod_strdup(s, "\4\14\15");
	if (!cmd->args[j])
		return (-1);
	(*i) += ft_strlen(cmd->args[j]);
	cmd->args[j] = ft_strshrinker(cmd->args[j], "\e\a\5\6", 1);
	return (0);
}

char	**split_args(char *cmd, t_enviroment *enviroment, int struct_i)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == RED_RIGHT || cmd[i] == RED_LEFT)
		{
			if (manage_redirections(cmd, enviroment, struct_i, &i) == -1)
				return (NULL);
		}
		else if ((i == 0 && !ft_isinstr("\4\14\15", cmd[i]))
			|| (!ft_isinstr("\4\14\15", cmd[i])
				&& ft_isinstr("\4\14\15", cmd[i - 1])))
		{
			if (create_arg(enviroment->cmd[struct_i], &cmd[i], &i, j) == -1)
				return (NULL);
			j++;
		}
		else
			i++;
	}
	return (enviroment->cmd[struct_i]->args);
}

int	check_priorities(t_cmd **cmd, t_enviroment *enviroment, int i,
		t_pipe *pipes)
{
	if (cmd[i]-> priorities != PIPE)
	{
		ft_close_pipes(pipes);
		waitpid(enviroment->child_pid[i - 1], (int *)&enviroment->status, 0);
		if (WIFEXITED(enviroment->status))
			enviroment->status = WEXITSTATUS(enviroment->status);
	}
	if ((cmd[i]->priorities == AND && enviroment->status != 0)
		|| (cmd[i]->priorities == OR && enviroment->status == 0)
		|| (cmd[i]->priorities == PIPE && enviroment->status != 0 && i != 0))
		return (1);
	return (0);
}
