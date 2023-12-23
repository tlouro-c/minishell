/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/23 14:22:50 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_enviroment
{
	t_node			*variables;
	char			**variables_array;
	char			*prompt;
	unsigned int	last_exit_status;
	int				stdin_fd;
	int				stdout_fd;
}	t_enviroment;

/* -------------------------------------------------------------------------- */
/*                                  built_ins                                 */
/* -------------------------------------------------------------------------- */

void		cmd_pwd(void);
void		cmd_env(t_node *enviroment_variables);
void		cmd_echo(char **args);
void		cmd_exit(char **args, t_enviroment *enviroment);

/* -------------------------------------------------------------------------- */
/*                                 manage_env                                 */
/* -------------------------------------------------------------------------- */

void		load_enviroment_variables(t_enviroment *enviroment);
char		*ft_getenv(char *key, t_node *enviroment_variables);
char		**updated_enviroment_variables_array(t_enviroment *enviroment);
int			ft_keycmp(char *keyvalue, char *key);

/* -------------------------------------------------------------------------- */
/*                                  exit_utils                                */
/* -------------------------------------------------------------------------- */

void		error_allocating_memory(t_enviroment *enviroment);
void		free_enviroment(t_enviroment *enviroment);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

char		*user_prompt(t_enviroment *enviroment);
size_t		ft_strarr_size(char **strarr);

/* -------------------------------------------------------------------------- */
/*                              manage_user_input                             */
/* -------------------------------------------------------------------------- */

char		*swap_env_in_input(char *input, t_enviroment *enviroment);

#endif /* MINISHELL_H */
