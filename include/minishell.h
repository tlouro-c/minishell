/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 16:06:19 by tlouro-c         ###   ########.fr       */
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

# define READ_END 0
# define WRITE_END 1

/* -> Colors  <- */
# define RESET "\x1B[0m"
# define CYAN "\033[1m\033[36m"
# define MAGENTA "\033[1m\033[35m"

# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

typedef struct s_pipe
{
	int	pipes[2];
	int	input_pipe[2];
	int	input_for_next;
}	t_pipe;

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
	int				fd_in;
	int				fd_out;
}	t_enviroment;

typedef struct s_modes
{
	int	s_q;
	int	d_q;
}	t_modes;

//? ------------------------------------------------------------------------ */
//?                               user_interface                             */
//? ------------------------------------------------------------------------ */

void		load_prompt(t_enviroment *enviroment); // ✅
void		welcome_message(void); // ✅

//? ------------------------------------------------------------------------ */
//?                                  built_ins                               */
//? ------------------------------------------------------------------------ */

int			cmd_pwd(void); // ✅
int			cmd_env(char **args, t_list *variables); // ✅
int			cmd_echo(char **args); // ✅
void		cmd_exit(char **args, t_enviroment *enviroment); // ✅
int			cmd_export(char **cmd, t_enviroment *enviroment); // ✅
int			cmd_unset(char **cmd, t_enviroment *enviroment); // ✅
int			cmd_cd(t_enviroment *enviroment, char **args); // ✅
int			cmd_help(void); // ✅

//? ------------------------------------------------------------------------ */
//?                                 manage_env                               */
//? ------------------------------------------------------------------------ */

void		load_enviroment_variables(t_enviroment *enviroment);
char		*ft_getenv(const char *key, t_list *variables);
int			ft_keycmp(void *keyvalue, void *key);
char		*ft_getkey(char *buffer, char *s);
int			ft_keylen(const char *key);

//? ------------------------------------------------------------------------ */
//?                                  exit_utils                              */
//? ------------------------------------------------------------------------ */

void		error_allocating_memory(t_enviroment *enviroment);
void		error_piping(t_enviroment *enviroment, int (*pipes)[2]);
void		error_and_close_pipes(t_enviroment *enviroment, int (*pipes)[2]);
void		error_allocating_memory_free_str(t_enviroment *enviroment, char *s);
void		free_enviroment(t_enviroment *enviroment);

//? ------------------------------------------------------------------------ */
//?                               error_messages                             */
//? ------------------------------------------------------------------------ */

void		invalid_option(char *cmd, char *option);
void		invalid_identifier(char *cmd, char *arg);

//? ------------------------------------------------------------------------ */
//?                                    utils                                 */
//? ------------------------------------------------------------------------ */

size_t		ft_strarr_size(char **strarr);
int			ft_isbuiltin(char *cmd);
int			run_builtin(t_cmd *cmd, t_enviroment *enviroment);
int			ft_key_only_snake(char *s);

/* -------------------------------------------------------------------------- */
/*                                   parser                                   */
/* -------------------------------------------------------------------------- */

char		*phase2(char *in, t_enviroment *enviroment);
char		*phase1(char *in);
void		load_commands(t_enviroment *enviroment, char *in);
char		**split_args(char *cmd, t_enviroment *enviroment, int struct_i);
void		pathfinder(t_enviroment *enviroment);
void		execute_cmds(t_cmd **commands, t_enviroment *enviroment);


//? ------------------------------------------------------------------------ */
//?                                  execute                                 */
//? ------------------------------------------------------------------------ */

//? ------------------------------------------------------------------------ */
//?                               manage_files                               */
//? ------------------------------------------------------------------------ */

int			read_here_doc(char *delimiter, int to_fd);
int			read_from_to(int from_fd, int to_fd);
void		fill_output_files(t_cmd *cmd, t_enviroment *enviroment, t_pipe pipes);

#endif /* MINISHELL_H */
