/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:23:28 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/15 00:26:46 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	manage_redirections(char *s, t_enviroment *enviroment,
				int struct_i, int *string_i)
{
	int		first;
	int		second;
	char	*file_or_delimiter;

	first = s[*string_i];
	second = s[*string_i + 1];
	while (s[*string_i] == '\4' || s[*string_i] == RED_LEFT
		|| s[*string_i] == RED_RIGHT || s[*string_i] == '\5'
		|| s[*string_i] == '\6')
		(*string_i)++;
	file_or_delimiter = mod_strdup(&s[*string_i], "\4\5\6\14\15");
	if (!file_or_delimiter)
		return (-1);
	(*string_i) += ft_strlen(file_or_delimiter);
	if (first == RED_LEFT && second == RED_LEFT)
		enviroment->cmd[struct_i]->delimiter->add(
			enviroment->cmd[struct_i]->delimiter, file_or_delimiter);
	else if (first == RED_LEFT)
		enviroment->cmd[struct_i]->input_file = file_or_delimiter;
	else if (first == RED_RIGHT && second == RED_RIGHT)
		enviroment->cmd[struct_i]->append_file = file_or_delimiter;
	else if (first == RED_RIGHT)
		enviroment->cmd[struct_i]->output_file = file_or_delimiter;
	return (1);
}

static int	create_arg(t_cmd *cmd, char *s, int *i, int j)
{
	cmd->args[j] = mod_strdup(s, "\4\14\15");
	if (!cmd->args[j])
		return (-1);
	if (cmd->args[j][0] == NULL_BYTE)
	{
		cmd->args[j][0] = '\0';
		(*i) += 2;
	}
	(*i) += ft_strlen(cmd->args[j]);
	cmd->args[j] = ft_strshrinker(cmd->args[j], "\e", 1);
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

int	check_priorities(t_cmd **cmd, t_enviroment *enviroment, int i)
{
	if (cmd[i]-> priorities != PIPE)
	{
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
