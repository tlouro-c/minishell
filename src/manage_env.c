/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:57:25 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/30 22:46:10 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	load_enviroment_variables(t_enviroment *enviroment)
{
	t_list		*variables;
	extern char	**environ;
	int			i;

	variables = new_list();
	if (!variables)
		error_allocating_memory(enviroment);
	i = 0;
	while (environ[i] != NULL)
	{
		if (variables->add(variables, ft_strdup(environ[i++])) == NULL)
			error_allocating_memory(enviroment);
	}
	enviroment->variables = variables;
	enviroment->last_exit_status = 0;
}

int	ft_keycmp(void *keyvalue, void *key)
{
	char	*char_keyvalue;
	char	*char_key;
	int		i;

	char_keyvalue = (char *)keyvalue;
	char_key = (char *)key;
	i = 0;
	if (char_keyvalue == NULL || char_key == NULL)
		return (0);
	while (ft_isalphanum(char_keyvalue[i]) && ft_isalphanum(char_key[i])
		&& char_keyvalue[i] == char_key[i])
		i++;
	return (char_keyvalue[i] != '=');
}

int	ft_keylen(const char *key)
{
	int	i;

	i = 0;
	while (ft_isalphanum(key[i]))
		i++;
	return (i);
}

char	*ft_getenv(const char *key, t_list *variables)
{
	t_node	*tmp;

	if (key == NULL || variables -> begin == NULL)
		return ("");
	tmp = variables -> begin;
	while (tmp)
	{
		if (ft_keycmp(tmp->value, (void *)key) == 0)
			return (tmp->value + ft_keylen(key) + 1);
		tmp = tmp->next;
	}
	return ("");
}
