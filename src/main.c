/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/19 16:46:10 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	main(void)
{
	char	**user_input;

	while (TRUE)
	{
		ft_printf("minishell ~%s $ ", ft_strnstr(getenv("PWD"), getenv("HOME"),
				ft_strlen(getenv("PWD"))) + ft_strlen(getenv("HOME")));
		user_input = ft_split(ft_get_next_line(0), ' ');
	}
}
