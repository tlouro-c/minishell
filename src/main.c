/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 10:50:19 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(void)
{
	t_enviroment		enviroment;
	char				*user_input;

	load_enviroment_variables(&enviroment);
	while (TRUE)
	{
		enviroment.prompt = user_prompt(&enviroment);
		user_input = readline(enviroment.prompt);
		if (!user_input)
			error_allocating_memory(&enviroment);
		else if (user_input[0] == '\0')
			continue ;
		add_history(user_input);
		load_commands(&enviroment, user_input);
		for (int i = 0; enviroment.cmd[i]; i++)
		{
			ft_printf("CMD %d\n", i);
			ft_printf("PRIORITY: %d\n", enviroment.cmd[i]->priorities);
			ft_printf("INPUT FILE: %s\n", enviroment.cmd[i]->input_file);
			ft_printf("OUTPUT FILE: %s\n", enviroment.cmd[i]->output_file);
			ft_printf("APPEND FILE: %s\n", enviroment.cmd[i]->append_file);
			ft_printf("DELIMITER: %s\n", enviroment.cmd[i]->delimiter);
			ft_printf("ARGUMENTS\n");
			for (int j = 0; enviroment.cmd[i]->args[j]; j++)
				ft_printf("\tARG %d: %s\n", j, enviroment.cmd[i]->args[j]);
		}
		execute_cmds(enviroment.cmd, &enviroment);
		// ft_printf("BEFORE: %s\n", user_input);
		// user_input = phase1(user_input);
		// user_input = phase2(user_input, &enviroment);
		// ft_printf("AFTER: %s\n", user_input);
		// char	**test = ft_split(user_input, '\2');
		// ft_printf ("[0] %s -> [1] %s -> [2] %s -> [3] %s\n", test[0], test[1], test[2], test[3]);
		// free_enviroment(&enviroment);
		// exit(0);
	}
}
