/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/25 01:01:47 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"


void	free_enviroment(t_enviroment *enviroment)
{
	if (enviroment->variables != NULL)
		ft_clear_list(&enviroment->variables);
	if (enviroment->variables_array != NULL)
		ft_free_str_arr(enviroment->variables_array, 
			ft_strarr_size(enviroment->variables_array));
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

