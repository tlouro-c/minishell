/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 01:01:18 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/25 01:20:55 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	invalid_option(char *cmd, char *option)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putchar_fd(option[0], 2);
	ft_putchar_fd(option[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
}

void	invalid_identifier(char *cmd, char *arg)
{
	char	key[1024];

	ft_memset(key, 0, 1024);
	ft_getkey(key, arg);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
