/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/27 17:14:34 by tlouro-c         ###   ########.fr       */
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
		add_history(user_input);
		char	**test = ft_split(user_input, ' ');
		if (ft_strcmp(test[0], "export") == 0)
			cmd_export(test, &enviroment);
		else if (ft_strcmp(test[0], "unset") == 0)
			cmd_unset(test, &enviroment);
		else if (ft_strcmp(test[0], "env") == 0)
			cmd_env(enviroment.variables);
		else if (ft_strcmp(test[0], "cd") == 0)
			cmd_cd(&enviroment, test[1]);	
		// free_enviroment(&enviroment);
		// exit(0);
	}
}
