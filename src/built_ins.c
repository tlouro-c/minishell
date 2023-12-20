/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 01:03:31 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	pwd(char **enviroment_variables)
{
	ft_printf("%s\n", ft_getenv("PWD", enviroment_variables));
}

void	env(char **enviroment_variables)
{
	int	i;

	i = 0;
	while (enviroment_variables[i] != NULL)
		ft_printf("%s\n", enviroment_variables[i++]);
}
