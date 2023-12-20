/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 23:22:51 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(void) 
{
	t_shell_enviroment	shell_enviroment;
	char				*user_input;
	
	shell_enviroment.last_exit_status = 0;
	shell_enviroment.variables = get_all_env();
	shell_enviroment.prompt = user_prompt(shell_enviroment.variables);
	while (TRUE)
	{
		user_input = readline(shell_enviroment.prompt);
		add_history(user_input);
		ft_printf("%s\n", swap_env_in_input(user_input, shell_enviroment.variables, shell_enviroment.last_exit_status));
		if (ft_strcmp(user_input, "env") == 0)
			env(shell_enviroment.variables);
		ft_free_str_arr(shell_enviroment.variables, ft_str_arr_size(shell_enviroment.variables));
		free(shell_enviroment.prompt);
		exit(1);
	}
}
