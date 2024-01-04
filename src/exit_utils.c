/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 11:37:11 by tlouro-c         ###   ########.fr       */
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

void	error_piping(t_enviroment *enviroment, int *pipes[2])
{
	free(pipes[2]);
	free_enviroment(enviroment);
	ft_putstr_fd("Error: piping failed\n", 2);
	exit(10);
}

void	error_allocating_memory_free_str(t_enviroment *enviroment, char *s)
{
	free(s);
	error_allocating_memory(enviroment);
}
