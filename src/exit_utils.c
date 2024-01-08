/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/05 17:58:01 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
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
void	error_and_close_pipes(t_enviroment *enviroment, int *pipes[2])
{
	//! Close pipes
	free(pipes[2]);
	free_enviroment(enviroment);
	ft_putstr_fd("Error.\n", 2);
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
