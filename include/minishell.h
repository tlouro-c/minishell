/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/28 00:56:36 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_enviroment
{
	t_list			*variables;
	char			*prompt;
	unsigned int	last_exit_status;
	int				stdin_fd;
	int				stdout_fd;
}	t_enviroment;

/* -------------------------------------------------------------------------- */
/*                                  built_ins                                 */
/* -------------------------------------------------------------------------- */

void		cmd_pwd(void);
void		cmd_env(t_list *variables);
void		cmd_echo(char **args);
void		cmd_exit(char **args, t_enviroment *enviroment);
void		cmd_export(char **cmd, t_enviroment *enviroment);
void		cmd_unset(char **cmd, t_enviroment *enviroment);
void		cmd_cd(t_enviroment *enviroment, char *path);

/* -------------------------------------------------------------------------- */
/*                                 manage_env                                 */
/* -------------------------------------------------------------------------- */

void		load_enviroment_variables(t_enviroment *enviroment);
char		*ft_getenv(const char *key, t_list *variables);
int			ft_keycmp(void *keyvalue, void *key);
char		*ft_getkey(char *buffer, char *s);

/* -------------------------------------------------------------------------- */
/*                                  exit_utils                                */
/* -------------------------------------------------------------------------- */

void		error_allocating_memory(t_enviroment *enviroment);
void		free_enviroment(t_enviroment *enviroment);

/* -------------------------------------------------------------------------- */
/*                               error_messages                               */
/* -------------------------------------------------------------------------- */

void		invalid_option(char *cmd, char *option);
void		invalid_identifier(char *cmd, char *arg);

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

char		*user_prompt(t_enviroment *enviroment);
size_t		ft_strarr_size(char **strarr);

/* -------------------------------------------------------------------------- */
/*                              manage_user_input                             */
/* -------------------------------------------------------------------------- */

char		*swap_env_in_input(char **input, t_enviroment *enviroment);

#endif /* MINISHELL_H */
