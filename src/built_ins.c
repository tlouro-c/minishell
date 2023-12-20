/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:46:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 22:50:36 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	pwd(void)
{
	ft_printf("%s\n", getenv("PWD"));
}

void	env(char **enviroment_variables)
{
	int	i;

	i = 0;
	while (enviroment_variables[i] != NULL)
		ft_printf("%s\n", enviroment_variables[i++]);
}
