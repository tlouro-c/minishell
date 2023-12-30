/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/30 20:28:31 by tlouro-c         ###   ########.fr       */
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
		ft_printf("BEFORE: %s\n", user_input);
		user_input = phase1(user_input, &enviroment);
		ft_printf("AFTER: %s\n", user_input);
		// char	**test = ft_split(user_input, '\2');
		// ft_printf ("[0] %s -> [1] %s -> [2] %s -> [3] %s\n", test[0], test[1], test[2], test[3]);
		// free_enviroment(&enviroment);
		// exit(0);
	}
}
