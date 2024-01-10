/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/10 20:59:57 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//valgrind --track-fds=yes --leak-check=full --gen-suppressions=all ./minishell

int	main(void)
{
	t_enviroment		enviroment;
	char				*user_input;

	load_enviroment_variables(&enviroment);
	welcome_message();
	while (TRUE)
	{
		setup_signals(MAIN);
		define_prompt(&enviroment);
		user_input = readline(enviroment.prompt);
		free(enviroment.prompt);
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
		execute_cmds(enviroment.cmd, &enviroment);
		wait_loop(&enviroment);
	}
}
