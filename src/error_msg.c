/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:55:02 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/21 22:48:12 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"


//! THIS FUNCTION HAS TO BE CHANGED FOR VERSATILITY
void	error_allocating_memory(t_enviroment *enviroment)
{
	(void)enviroment;
	ft_putstr_fd("Error: memory allocation failed\n", 2);
	exit(10);
}
