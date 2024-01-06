/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
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
	while (TRUE)
	{
		load_prompt(&enviroment);
		user_input = readline(enviroment.prompt);
		if (!user_input)
			error_allocating_memory(&enviroment);
		else if (user_input[0] == '\0')
			continue ;
		add_history(user_input);
		load_commands(&enviroment, user_input);
		execute_cmds(enviroment.cmd, &enviroment);
	}
}
