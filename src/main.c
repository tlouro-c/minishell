/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 15:53:06 by tlouro-c         ###   ########.fr       */

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
		load_prompt(&enviroment);
		user_input = readline(enviroment.prompt);
		/**
		 * unlike other signals this is also how EOF(ctrl+D) is caught
		*/
		if (!user_input)
			error_allocating_memory(&enviroment);
		add_history(user_input);
		if (load_commands(&enviroment, user_input) == -1)
			continue ;
		execute_cmds(enviroment.cmd, &enviroment);
		// free_enviroment(&enviroment);
		// exit(0);
	}
}
