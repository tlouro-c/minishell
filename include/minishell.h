/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 23:13:09 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell_enviroment
{
	char	**variables;
	char	*prompt;
	int		last_exit_status;
}			t_shell_enviroment;

/* -------------------------------------------------------------------------- */
/*                                  built_ins                                 */
/* -------------------------------------------------------------------------- */

void	pwd(char **enviroment_variables);
void	env(char **enviroment_variables);

/* -------------------------------------------------------------------------- */
/*                                 manage_env                                 */
/* -------------------------------------------------------------------------- */

char	**get_all_env(void);
char	*ft_getenv(char *key, char **env_var);

/* -------------------------------------------------------------------------- */
/*                                  error_msg                                 */
/* -------------------------------------------------------------------------- */

void	error_allocating_memory(void);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

int		ft_str_arr_size(char **strarr);
char	*user_prompt(char **env_var);

/* -------------------------------------------------------------------------- */
/*                              manage_user_input                             */
/* -------------------------------------------------------------------------- */

char	*swap_env_in_input(char *input, char **env_var, int last_exit_status);

#endif /* MINISHELL_H */
