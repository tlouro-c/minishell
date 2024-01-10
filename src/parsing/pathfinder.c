/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:51:23 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/10 21:18:44 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		j;
	int		i;

	s3 = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	if (!s3)
		return (s3);
	j = 0;
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
		s3[j++] = s1[i++];
	s3[j++] = '/';
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
		s3[j++] = s2[i++];
	s3[j] = '\0';
	return (s3);
}

static void	look_for_path(t_cmd	*cmd, t_enviroment *enviroment)
{
	char	*path;
	char	**paths;
	int		i;

	if (cmd->args[0][0] == '\0')
		return ;
	paths = ft_split(ft_getenv("PATH", enviroment->variables), ":");
	if (!paths)
		error_allocating_memory(enviroment);
	i = 0;
	while (paths[i])
	{
		path = ft_pathjoin(paths[i++], cmd->args[0]);
		if (!path)
			error_allocating_memory_free_arr(enviroment, (void **)paths);
		if (access(path, X_OK) == 0)
		{
			free(cmd->args[0]);
			cmd->args[0] = path;
			break ;
		}
		free(path);
	}
	ft_free_arr((void **)paths);
}

void	pathfinder(t_enviroment *enviroment)
{
	int	i;

	i = 0;
	while (enviroment->cmd[i])
	{
		if (!enviroment->cmd[i]->args[0])
		{
			enviroment->cmd[i]->valid = COMMAND_NOT_FOUND;
			return ;
		}
		if (!ft_isbuiltin(enviroment->cmd[i]))
			look_for_path(enviroment->cmd[i], enviroment);
		if (!ft_isbuiltin(enviroment->cmd[i])
			&& ft_strchr(enviroment->cmd[i]->args[0], '/') == NULL)
			enviroment->cmd[i]->valid = COMMAND_NOT_FOUND;
		else
			enviroment->cmd[i]->valid = COMMAND_FOUND;
		enviroment->cmd[i]->has_input_file = (enviroment->cmd[i]->input_file
				|| enviroment->cmd[i]->delimiter);
		i++;
	}
}
