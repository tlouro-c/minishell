/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/22 17:19:59 by tlouro-c         ###   ########.fr       */
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
	char	**variables_array;
	char		*prompt;
	int			last_exit_status;
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

t_node		*load_enviroment_variables(void);
char		*ft_getenv(char *key, t_node *enviroment_variables);
char		**create_enviroment_variables_array(t_enviroment *enviroment);
char		**updated_enviroment_variables_array(t_enviroment *enviroment);
int			ft_keycmp(char *keyvalue, char *key);

/* -------------------------------------------------------------------------- */
/*                                  error_msg                                 */
/* -------------------------------------------------------------------------- */

void		error_allocating_memory(t_enviroment *enviroment);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

char		*user_prompt(t_enviroment *enviroment);
size_t		ft_strarr_size(char **strarr);
long long	ft_atoll_base(const char *s, int base_size);

/* -------------------------------------------------------------------------- */
/*                              manage_user_input                             */
/* -------------------------------------------------------------------------- */

char		*swap_env_in_input(char *input, t_enviroment *enviroment);

#endif /* MINISHELL_H */
