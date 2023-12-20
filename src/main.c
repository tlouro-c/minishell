/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 00:53:34 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(void)
{
	char		**env_var;
	char		**user_input;
	int			last_exit_status;

	last_exit_status = 0;
	env_var = get_all_env();
	while (TRUE)
	{
		user_prompt(env_var);
		user_input = ft_split(ft_get_next_line_v2(0), ' ');
		ft_printf("%s\n", find_env_in_input(user_input[0], env_var, last_exit_status));
	}
}
