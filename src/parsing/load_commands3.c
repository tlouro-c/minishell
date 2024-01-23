/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_commands3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:07:39 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/23 11:17:09 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	input_file(t_cmd *cmd, char **split, int before_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (split[i])
	{
		tmp = ft_strshrinker(split[i], "\e\a\5\6", 0);
		if (!tmp)
			return (-1);
		cmd->input_file->add(cmd->input_file, ft_strdup(tmp));
		free(tmp);
		if (before_cmd)
			break ;
		i++;
	}
	cmd->prio_in = IN;
	return (0);
}

int	append_file(t_cmd *cmd, char **split, int before_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (split[i])
	{
		tmp = ft_strshrinker(split[i], "\e\a\5\6", 0);
		if (!tmp)
			return (-1);
		cmd->append_file->add(cmd->append_file, ft_strdup(tmp));
		free(tmp);
		if (before_cmd)
			break ;
		i++;
	}
	cmd->prio_out = APP;
	return (0);
}

int	output_file(t_cmd *cmd, char **split, int before_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (split[i])
	{
		tmp = ft_strshrinker(split[i], "\e\a\5\6", 0);
		if (!tmp)
			return (-1);
		cmd->output_file->add(cmd->output_file, ft_strdup(tmp));
		free(tmp);
		if (before_cmd)
			break ;
		i++;
	}
	cmd->prio_out = OVE;
	return (0);
}

int	here_doc(t_cmd *cmd, char **split, int before_cmd)
{
	int		i;

	i = 0;
	while (split[i])
	{
		cmd->delimiter->add(cmd->delimiter, ft_strdup(split[i]));
		if (before_cmd)
			break ;
		i++;
	}
	cmd->prio_in = HERE;
	return (0);
}

void	setup_red_parsing(char *s, int *str_i, int *st, int *nd)
{
	*st = s[*str_i];
	*nd = s[*str_i + 1];
	while (s[*str_i] == '\4' || s[*str_i] == RED_LEFT
		|| s[*str_i] == RED_RIGHT)
		(*str_i)++;
}
