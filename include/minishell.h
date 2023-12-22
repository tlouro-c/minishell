/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 14:01:19 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_enviroment
{
	t_node	*variables;
	char		*prompt;
	int			last_exit_status;
}	t_enviroment;

/* -------------------------------------------------------------------------- */
/*                                  built_ins                                 */
/* -------------------------------------------------------------------------- */

void	pwd(void);
void	env(t_node *enviroment_variables);

/* -------------------------------------------------------------------------- */
/*                                 manage_env                                 */
/* -------------------------------------------------------------------------- */

t_node	*load_enviroment_variables(void);
char	*ft_getenv(char *key, t_node *enviroment_variables);

/* -------------------------------------------------------------------------- */
/*                                  error_msg                                 */
/* -------------------------------------------------------------------------- */

void	error_allocating_memory(t_enviroment *enviroment);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

char	*user_prompt(t_enviroment *enviroment);

/* -------------------------------------------------------------------------- */
/*                              manage_user_input                             */
/* -------------------------------------------------------------------------- */

char	*swap_env_in_input(char *input, t_enviroment *enviroment);

#endif /* MINISHELL_H */
