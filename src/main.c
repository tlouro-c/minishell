/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/23 14:23:20 by tlouro-c         ###   ########.fr       */
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
		free_enviroment(&enviroment);
		exit(0);
	}
}
