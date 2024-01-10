/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:51:49 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/09 18:01:50 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*get_env_declare(char *enviroment_variable)
{
	char	*env_declare;
	int		i;
	int		j;

	env_declare = ft_calloc(ft_strlen(enviroment_variable) + 3, sizeof(char));
	if (!env_declare)
		return (NULL);
	i = 0;
	j = 0;
	while (enviroment_variable[i] != '\0' && enviroment_variable[i] != '=')
		env_declare[j++] = enviroment_variable[i++];
	if (enviroment_variable[i] == '=')
	{
		env_declare[j++] = '=';
		env_declare[j++] = '"';
		i++;
	}
	while (enviroment_variable[i] != '\0')
		env_declare[j++] = enviroment_variable[i++];
	if (i != j)
		env_declare[j++] = '"';
	env_declare[j] = '\0';
	return (env_declare);
}

void	set_pwd(t_enviroment *enviroment)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd)
		error_allocating_memory(enviroment);
	enviroment->variables->set(enviroment->variables, "PWD", pwd, ft_keycmp);
}

void	set_oldpwd(t_enviroment *enviroment)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", ft_getenv("PWD", enviroment ->variables));
	if (!oldpwd)
		error_allocating_memory(enviroment);
	enviroment->variables->set(enviroment->variables, "OLDPWD",
		oldpwd, ft_keycmp);
}
