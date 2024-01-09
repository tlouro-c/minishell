/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/08 19:47:30 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd->args)
		ft_free_arr((void **)cmd->args);
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	if (cmd->append_file)
		free(cmd->append_file);
	if (cmd->delimiter)
		free(cmd->delimiter);
	free(cmd);
}

void	free_cmds(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		free_cmd(cmd[i]);
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
