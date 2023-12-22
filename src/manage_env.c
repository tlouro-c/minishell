/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:57:25 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 13:32:47 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_node	*load_enviroment_variables(void)
{
	t_node		*variables;
	extern char	**environ;
	int			i;

	variables = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		ft_insert_at_beginning(&variables, (char *)ft_strdup(environ[i]));
		i++;
	}
	return (variables);
}

static int	ft_foundpair(char *keyvalue, char *key)
{
	int	i;

	i = 0;
	while (keyvalue[i] != '\0' && key[i] != '\0' && keyvalue[i] == key[i])
		i++;
	return (keyvalue[i] == '=');
}

char	*ft_getenv(char *key, t_node *enviroment_variables)
{
	t_node	*tmp;
	
	if (key == NULL || enviroment_variables == NULL)
		return ("");
	tmp = enviroment_variables;
	while (tmp != NULL)
	{
		if (ft_foundpair(tmp->content, key))
			return (tmp->content + ft_strlen(key) + 1);
		tmp = tmp->next;
	}
	return ("");
}
