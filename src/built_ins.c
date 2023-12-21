/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/21 15:19:54 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	pwd(t_shell_enviroment *shell_enviroment)
{
	ft_printf("%s\n", ft_getenv("PWD", shell_enviroment -> variables));
}

void	env(t_shell_enviroment *shell_enviroment)
{
	int	i;

	i = 0;
	while (shell_enviroment -> variables[i] != NULL)
		ft_printf("%s\n", shell_enviroment -> variables[i++]);
}

