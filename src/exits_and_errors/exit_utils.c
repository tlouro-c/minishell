/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/09 20:54:59 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_allocating_memory(t_enviroment *enviroment)
{
	ft_putstr_fd("Error: memory allocation failed\n", 2);
	free_exit(enviroment, 10);
}

void	error_and_close_pipes(t_enviroment *enviroment, t_pipe *pipes)
{
	ft_close_pipes(pipes);
	free_enviroment(enviroment);
	ft_putstr_fd("Error: exiting...\n", 2);
	exit(10);
}

void	error_piping(t_enviroment *enviroment, t_pipe pipes)
{
	ft_close_pipes(&pipes);
	free_enviroment(enviroment);
	ft_putstr_fd("Error: piping failed\n", 2);
	exit(10);
}

void	error_allocating_memory_free_str(t_enviroment *enviroment, char *s)
{
	free(s);
	error_allocating_memory(enviroment);
}

void	error_allocating_memory_free_arr(t_enviroment *enviroment, void **arr)
{
	ft_free_arr(arr);
	ft_putstr_fd("Error: memory allocation failed\n", 2);
	free_exit(enviroment, 10);
}
