/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:51:23 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 00:29:42 by tlouro-c         ###   ########.fr       */
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

static void	look_for_path(char **cmd, t_enviroment *enviroment)
{
	char	*path;
	char	**paths;
	int		i;

	paths = ft_split(ft_getenv("PATHS", enviroment->variables), ":");
	if (!paths)
		error_allocating_memory(enviroment);
	i = 0;
	while (paths[i])
	{
		path = ft_pathjoin(paths[i++], *cmd);
		if (!path)
			error_allocating_memory(enviroment);
		if (access(path, X_OK) == 0)
		{
			free(*cmd);
			*cmd = path;
			break ;
		}
		free(path);
	}
}

void	pathfinder(t_enviroment *enviroment)
{
	int	i;

	i = 0;
	while (enviroment->cmd[i])
	{
		if (!ft_isbuiltin(enviroment->cmd[i]->args[0]))
			look_for_path(&enviroment->cmd[i]->args[0], enviroment);
		i++;
	}
}
