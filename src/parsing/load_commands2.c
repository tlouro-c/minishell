/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:23:28 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/08 17:19:07 by tlouro-c         ###   ########.fr       */
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
	while (s[*string_i] == '\4' || s[*string_i] == '<' || s[*string_i] == '>'
		|| s[*string_i] == '\5' || s[*string_i] == '\6')
		(*string_i)++;
	file_or_delimiter = mod_strdup(&s[*string_i], "\4\5\6<>");
	if (!file_or_delimiter)
		return (-1);
	(*string_i) += ft_strlen(file_or_delimiter);
	if (first == '<' && second == '<')
		enviroment->cmd[struct_i]->delimiter = file_or_delimiter;
	else if (first == '<')
		enviroment->cmd[struct_i]->input_file = file_or_delimiter;
	else if (first == '>' && second == '>')
		enviroment->cmd[struct_i]->append_file = file_or_delimiter;
	else if (first == '>')
		enviroment->cmd[struct_i]->output_file = file_or_delimiter;
	return (1);
}

char	**split_args(char *cmd, t_enviroment *enviroment, int struct_i)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (manage_redirections(cmd, enviroment, struct_i, &i) == -1)
				return (NULL);
		}
		else if ((i == 0 && !ft_isinstr("\4\5\6<>", cmd[i]))
			|| (!ft_isinstr("\4\5\6<>", cmd[i])
				&& ft_isinstr("\4\5\6<>", cmd[i - 1])))
		{
			enviroment->cmd[struct_i]->args[j] = mod_strdup(&cmd[i], "\4\5\6<>");
			if (!enviroment->cmd[struct_i]->args[j])
				return (NULL);
			i += ft_strlen(enviroment->cmd[struct_i]->args[j++]);
		}
		else
			i++;
	}
	return (enviroment->cmd[struct_i]->args);
}
