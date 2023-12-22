/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 14:02:02 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(void) 
{
	t_enviroment	enviroment;
	char				*user_input;

	enviroment.variables = load_enviroment_variables();
	while (TRUE)
	{
		enviroment.prompt = user_prompt(&enviroment);
		user_input = readline(enviroment.prompt);
		add_history(user_input);
		
	}
}
