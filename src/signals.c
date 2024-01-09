/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:01:41 by dabalm            #+#    #+#             */
/*   Updated: 2024/01/09 16:43:06 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void handle_sigint_child(int sig)
{
    (void)sig;
    exit(128 + SIGINT);
}


void handle_sigint_main(int sig)
{
    (void)sig;
    
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("\033[1m\033[35mminishell>\x1B[0m ", 2);
    rl_replace_line("", 0);
}

void setup_sigquit_handler(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGQUIT, &sa, NULL);
}

void setup_signals(int n)
{
    struct sigaction sa;

    setup_sigquit_handler();
    if (n == MAIN)
    {
        sa.sa_handler = handle_sigint_main;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
    } else if (n == CHILD) {
        sa.sa_handler = handle_sigint_child;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
    }
}