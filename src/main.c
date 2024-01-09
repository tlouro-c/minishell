/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/09 16:45:28 by dabalm           ###   ########.fr       */
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
	while (TRUE)
	{
		setup_signals(MAIN);
		if (enviroment.prompt_mode == LONG)
			load_prompt(&enviroment);
		else
			enviroment.prompt = ft_strdup("\033[1m\033[35mminishell>\x1B[0m "); 
		ft_putstr_fd(enviroment.prompt, 2);
		user_input = readline(NULL);
		free(enviroment.prompt);
		/**
		 * unlike other signals this is also how EOF(ctrl+D) is caught
		*/
		if (!user_input)
			free_exit(&enviroment, 2);
		if (user_input[0] == '\0')
		{
			free(user_input);
			continue ;
		}
		add_history(user_input);
		if (load_commands(&enviroment, user_input) == -1)
			continue ;
		order_cmd(enviroment.cmd);
		execute_cmds(enviroment.cmd, &enviroment);
	}
}
