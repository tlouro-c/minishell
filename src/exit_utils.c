/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 13:23:34 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_enviroment(t_enviroment *enviroment)
{
	enviroment->variables->destroy(enviroment->variables);
	if (enviroment->prompt != NULL)
		free(enviroment->prompt);
	//! LACKING COMMANDS STRUCTURE TO BE FREED
}

void	error_allocating_memory(t_enviroment *enviroment)
{
	free_enviroment(enviroment);
	ft_putstr_fd("Error: memory allocation failed\n", 2);
	exit(10);
}
