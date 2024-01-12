/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:49:46 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/12 10:55:44 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	set_up_main_signals(struct sigaction *sa, int n)
{
	if (n == MAIN)
	{
		sa->sa_handler = handle_sigint_main;
		sigemptyset(&sa->sa_mask);
		sa->sa_flags = 0;
		sigaction(SIGINT, sa, NULL);
	}
	else if (n == MAIN2)
	{
		sa->sa_handler = handle_sigint_main2;
		sigemptyset(&sa->sa_mask);
		sa->sa_flags = 0;
		sigaction(SIGINT, sa, NULL);
	}
}
