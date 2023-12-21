/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:57:25 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/21 14:59:17 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_strncmp_env(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s2[i] != '\0' && s1[i] != '\0' && i < n - 1)
		i++;
	if (s1[i + 1] != '=')
		return (-1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	**ft_get_all_env(void)
{
	extern char	**environ;
	char		**env_var;
	int			i;

	i = 0;
	env_var = NULL;
	env_var = (char **)ft_calloc(ft_str_arr_size(environ) + 1, sizeof(char *));
	if (env_var == NULL)
		error_allocating_memory();
	while (environ[i] != NULL)
	{
		env_var[i] = ft_strdup(environ[i]);
		if (env_var[i] == NULL)
		{
			ft_free_str_arr(env_var, i);
			error_allocating_memory();
		}
		i++;
	}
	env_var[i] = NULL;
	return (env_var);
}

char	*ft_getenv(char *key, char **env_var)
{
	int	i;
	int	key_len;

	if (key == NULL || env_var == NULL)
		return ("");
	key_len = ft_strlen(key);
	i = 0;
	while (env_var[i] != NULL)
	{
		if (ft_strncmp_env(env_var[i], key, key_len) == 0)
			return (env_var[i] + key_len + 1);
		i++;
	}
	return ("");
}

int	ft_get_indexenv(char *key, char **env_var)
{
	int	index;
	int	key_len;

	if (key == NULL || env_var == NULL)
		return (-1);
	key_len = ft_strlen(key);
	index = 0;
	while (env_var[index] != NULL)
	{
		if (ft_strncmp_env(env_var[index], key, key_len) == 0)
			return (index);
		index++;
	}
	return (-1);
}
