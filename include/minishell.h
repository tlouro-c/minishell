/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/04 23:22:22 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ON 1
# define OFF 0

# define PIPE 1
# define AND 2
# define OR 3
# define SPACE 4
# define S_QUOTE 5
# define D_QUOTE 6

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

enum e_mode
{
	OVERWRITE,
	APPEND
};

typedef struct s_cmd
{
	char	**args;
	int		priorities;
	char	*input_file;
	char	*output_file;
	char	*append_file;
	char	*delimiter;
}	t_cmd;

typedef struct s_enviroment
{
	t_list			*variables;
	t_cmd			**cmd;
	size_t			num_cmd;
	char			*prompt;
	unsigned int	status;
}	t_enviroment;

typedef struct s_modes
{
	int	s_q;
	int	d_q;
}	t_modes;

/* -------------------------------------------------------------------------- */
/*                                  built_ins                                 */
/* -------------------------------------------------------------------------- */

int			cmd_pwd(char **args);
int			cmd_env(char **args, t_list *variables);
int			cmd_echo(char **args);
void		cmd_exit(char **args, t_enviroment *enviroment);
int			cmd_export(char **cmd, t_enviroment *enviroment);
int			cmd_unset(char **cmd, t_enviroment *enviroment);
int			cmd_cd(t_enviroment *enviroment, char **args);

/* -------------------------------------------------------------------------- */
/*                                 manage_env                                 */
/* -------------------------------------------------------------------------- */

void		load_enviroment_variables(t_enviroment *enviroment);
char		*ft_getenv(const char *key, t_list *variables);
int			ft_keycmp(void *keyvalue, void *key);
char		*ft_getkey(char *buffer, char *s);
int			ft_keylen(const char *key);

/* -------------------------------------------------------------------------- */
/*                                  exit_utils                                */
/* -------------------------------------------------------------------------- */

void		error_allocating_memory(t_enviroment *enviroment);
void		error_piping(t_enviroment *enviroment, int (*pipes)[2]);
void		error_and_close_pipes(t_enviroment *enviroment, int (*pipes)[2]);
void		error_allocating_memory_free_str(t_enviroment *enviroment, char *s);
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
int			ft_isbuiltin(char *cmd);
int			run_builtin(t_cmd *cmd, t_enviroment *enviroment);

/* -------------------------------------------------------------------------- */
/*                                   parser                                   */
/* -------------------------------------------------------------------------- */

char		*phase2(char *in, t_enviroment *enviroment);
char		*phase1(char *in);
void		load_commands(t_enviroment *enviroment, char *in);
char		**split_args(char *cmd, t_enviroment *enviroment, int struct_i);
void		pathfinder(t_enviroment *enviroment);

void		execute_cmds(t_cmd **commands, t_enviroment *enviroment);
int			read_from_to(int from_fd, int to_fd);
int			manage_output(t_cmd **commands, int (*pipes)[2], int i);
void		close_pipes_child(int (*pipes)[2], int i, t_enviroment *enviroment);

#endif /* MINISHELL_H */
