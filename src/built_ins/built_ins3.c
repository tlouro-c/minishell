/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:41:24 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 21:58:58 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	cmd_prompt(t_cmd *cmd, t_enviroment *enviroment)
{
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "--short") == 0)
	{
		enviroment->prompt_mode = SHORT;
		return (0);
	}
	else if (cmd->args[1] && ft_strcmp(cmd->args[1], "--long") == 0)
	{
		enviroment->prompt_mode = LONG;
		return (0);
	}
	return (0);
}
