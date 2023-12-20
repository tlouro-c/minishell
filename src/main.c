/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 18:29:22 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(void) 
{
	char		**env_var;
	char		*user_input;
	int			last_exit_status;

	last_exit_status = 0;
	(void)last_exit_status;
	env_var = get_all_env();
	while (TRUE)
	{
		user_prompt(env_var);
		user_input = readline("");
		ft_printf("%s\n", user_input);
	}
}
