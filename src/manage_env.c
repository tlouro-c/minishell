/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:57:25 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/23 14:21:45 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	load_enviroment_variables(t_enviroment *enviroment)
{
	t_node		*variables;
	extern char	**environ;
	int			i;

	variables = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_insert_at_beginning(&variables, ft_strdup(environ[i])) == NULL)
			error_allocating_memory(enviroment);
		i++;
	}
	enviroment->variables = variables;
	enviroment->variables_array = NULL;
}

static char	**create_enviroment_variables_array(t_enviroment *enviroment)
{
	t_node	*tmp;
	char	**enviroment_variables_array;
	int		i;

	enviroment_variables_array = (char **)ft_calloc(
			ft_list_size(enviroment -> variables) + 1, sizeof(char *));
	if (enviroment_variables_array == NULL)
		error_allocating_memory(enviroment);
	tmp = enviroment -> variables;
	i = 0;
	while (tmp != NULL)
	{
		enviroment_variables_array[i] = tmp -> content;
		i++;
		tmp = tmp -> next;
	}
	enviroment_variables_array[i] = NULL;
	return (enviroment_variables_array);
}

char	**updated_enviroment_variables_array(t_enviroment *enviroment)
{
	free(enviroment -> variables_array);
	return (create_enviroment_variables_array(enviroment));
}

int	ft_keycmp(char *keyvalue, char *key)
{
	int	i;

	i = 0;
	if (keyvalue == NULL || key == NULL)	
		return (0);
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
		if (ft_keycmp(tmp->content, key))
			return (tmp->content + ft_strlen(key) + 1);
		tmp = tmp->next;
	}
	return ("");
}
