/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/08 17:58:11 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(void)
{
	t_enviroment		enviroment;
	char				*user_input;

	load_enviroment_variables(&enviroment);
	welcome_message();
	// setup_signals();
	while (TRUE)
	{
		if (enviroment.prompt_mode == LONG)
			load_prompt(&enviroment);
		else
			enviroment.prompt = ft_strdup("\033[1m\033[35mminishell>\x1B[0m "); 
		user_input = readline(enviroment.prompt);
		free(enviroment.prompt);
		/**
		 * unlike other signals this is also how EOF(ctrl+D) is caught
		*/
		if (!user_input)
			error_allocating_memory(&enviroment);
		if (user_input[0] == '\0')
		{
			free(user_input);
			continue;
		}
		add_history(user_input);
		if (load_commands(&enviroment, user_input) == -1)
			continue ;
		execute_cmds(enviroment.cmd, &enviroment);
	}
}
