/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __destroy_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:59:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/22 20:10:57 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	__destroy_node(t_node *this, int free_value)
{
	if (free_value)
		free(this -> value);
	free(this);
}
