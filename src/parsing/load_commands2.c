/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:23:28 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/23 16:01:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	free_and_reassign(t_cmd *cmd, char **split, int prio,
	int before_cmd)
{
	if (prio == IN)
		input_file(cmd, split, before_cmd);
	else if (prio == APP)
		append_file(cmd, split, before_cmd);
	else if (prio == OVE)
		output_file(cmd, split, before_cmd);
	else if (prio == HERE)
		here_doc(cmd, split, before_cmd);
}

static int	manage_redirections(char *s, t_cmd *cmd, int *str_i)
{
	int		st;
	int		nd;
	int		before_cmd;
	char	*tmp;
	char	**split;

	before_cmd = !cmd->args[0];
	setup_red_parsing(s, str_i, &st, &nd);
	tmp = mod_strdup(&s[*str_i], "\x0E\x0F");
	split = ft_split(tmp, "\4");
	if (st == RED_LEFT && nd == RED_LEFT)
		free_and_reassign(cmd, split, HERE, before_cmd);
	else if (st == RED_LEFT)
		free_and_reassign(cmd, split, IN, before_cmd);
	else if (st == RED_RIGHT && nd == RED_RIGHT)
		free_and_reassign(cmd, split, APP, before_cmd);
	else if (st == RED_RIGHT)
		free_and_reassign(cmd, split, OVE, before_cmd);
	if (before_cmd)
		(*str_i) += ft_strlen(split[0]);
	else
		(*str_i) += ft_strlen(tmp);
	free(tmp);
	ft_free_arr((void **)split);
	return (1);
}

static int	create_arg(t_cmd *cmd, char *s, int *i, int j)
{
	cmd->args[j] = mod_strdup(s, "\4\x0E\x0F");
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
			if (manage_redirections(cmd, enviroment->cmd[struct_i], &i) == -1)
				return (NULL);
		}
		else if ((i == 0 && !ft_isinstr("\4\x0E\x0F", cmd[i]))
			|| (!ft_isinstr("\4\x0E\x0F", cmd[i])
				&& ft_isinstr("\4\x0E\x0F", cmd[i - 1])))
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
		|| (cmd[i]->priorities == OR && enviroment->status == 0))
		return (1);
	return (0);
}
