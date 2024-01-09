/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:07:29 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/09 11:05:22 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	welcome_message(void)
{
	ft_printf("\n%s*************************************************\n\n",
		CYAN);
	ft_printf("   Welcome to minishell - By %sdabalm%s & %stlouro-c%s  \n\n",
		MAGENTA, CYAN, MAGENTA, CYAN);
	ft_printf("*************************************************%s\n\n", RESET);
	ft_printf("  %s  Ready to explore? Type 'minishell --help'\n\n", CYAN);
	ft_printf("              Start coding now! 💻%s\n\n", RESET);
}

static char	*path_for_prompt(t_enviroment *enviroment)
{
	char	*path;
	char	*pwd;
	char	*home;
	int		home_len;

	home = ft_getenv("HOME", enviroment->variables);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		error_allocating_memory(enviroment);
	home_len = ft_strlen(home);
	if (home_len > 0 && ft_strnstr(pwd, home, home_len))
	{
		path = ft_strjoin("~", pwd + home_len);
		free(pwd);
		if (!path)
			return (NULL);
	}
	else
		path = pwd;
	return (path);
}

void	load_prompt(t_enviroment *enviroment)
{
	char	*str_to_join[6];
	char	*tmp;
	int		i;

	enviroment -> prompt = NULL;
	str_to_join[0] = MAGENTA;
	str_to_join[1] = ft_getenv("USER", enviroment->variables);
	str_to_join[2] = "@minishell:\033[1m\033[36m";
	str_to_join[3] = path_for_prompt(enviroment);
	if (!str_to_join[3])
		error_allocating_memory(enviroment);
	str_to_join[4] = "$ \e[0m";
	str_to_join[5] = NULL;
	i = -1;
	while (str_to_join[++i] != NULL)
	{
		tmp = enviroment->prompt;
		enviroment->prompt = ft_strjoin(enviroment->prompt, str_to_join[i]);
		free(tmp);
		if (i == 3)
			free(str_to_join[i]);
		if (enviroment->prompt == NULL)
			error_allocating_memory(enviroment);
	}
}
