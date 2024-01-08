/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/08 17:31:01 by dabalm           ###   ########.fr       */
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

void	free_exit(t_enviroment *enviroment, int status)
{
	free_enviroment(enviroment);
	exit(status);
}

void	free_enviroment(t_enviroment *enviroment)
{
	enviroment->variables->destroy(enviroment->variables);
	free_cmds(enviroment->cmd);
}

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
	close(pipes.pipes[0]);
	close(pipes.pipes[1]);
	close(pipes.input_pipe[0]);
	close(pipes.input_pipe[1]);
	if (pipes.input_for_next != STDIN_FILENO)
		close(pipes.input_for_next);
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
