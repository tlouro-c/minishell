/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 19:59:40 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_cmds(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->args)
			ft_free_arr((void **)cmd[i]->args);
		if (cmd[i]->input_file)
			free(cmd[i]->input_file);
		if (cmd[i]->output_file)
			free(cmd[i]->output_file);
		if (cmd[i]->append_file)
			free(cmd[i]->append_file);
		if (cmd[i]->delimiter)
			free(cmd[i]->delimiter);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_enviroment(t_enviroment *enviroment)
{
	enviroment->variables->destroy(enviroment->variables);
	if (enviroment->prompt != NULL)
		free(enviroment->prompt);
	free_cmds(enviroment->cmd);
	//! LACKING COMMANDS STRUCTURE TO BE FREED
}

void	error_allocating_memory(t_enviroment *enviroment)
{
	free_enviroment(enviroment);
	exit(10);
}

void	error_allocating_memory_free_str(t_enviroment *enviroment, char *s)
{
	free(s);
	error_allocating_memory(enviroment);
}
