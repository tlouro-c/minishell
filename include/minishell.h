/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/06 22:36:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

# define ON 1
# define OFF 0

# define SHORT 0
# define LONG 1

# define COMMAND_NOT_FOUND 0
# define COMMAND_FOUND 1

# define PIPE 1
# define AND 2
# define OR 3
# undef SPACE
# define SPACE 4
# define S_QUOTE 5
# define D_QUOTE 5

# define READ_END 0
# define WRITE_END 1

# define RESET "\x1B[0m"
# define CYAN "\033[1m\033[36m"
# define MAGENTA "\033[1m\033[35m"

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
	int		valid;
	t_bool	has_output_file;
	t_bool	has_input_file;
}	t_cmd;

typedef struct s_enviroment
{
	t_list			*variables;
	t_cmd			**cmd;
	size_t			num_cmd;
	char			*prompt;
	int				parsing_error;
	unsigned int	last_exit_status;
	pid_t			child_pid;
	int				stdin_fd;
	int				stdout_fd;
	unsigned int	status;
	int				fd_in;
	int				fd_out;
	int				prompt_mode;
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

/* -------------------------------------------------------------------------- */
/*                                   signals                                  */
/* -------------------------------------------------------------------------- */

// void setup_signals(void);
// void handle_sigint(t_enviroment *enviroment);
// void signal_handler(int sig, siginfo_t *a, void *b);

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
int			cmd_prompt(t_cmd *cmd, t_enviroment *enviroment); // ✅

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
void		error_piping(t_enviroment *enviroment, t_pipe pipes);
void		error_and_close_pipes(t_enviroment *enviroment, t_pipe pipes);
void		error_allocating_memory_free_str(t_enviroment *enviroment, char *s);
void		error_allocating_memory_free_arr(t_enviroment *enviroment,
				void **arr);
void		free_enviroment(t_enviroment *enviroment);
void		free_cmds(t_cmd **cmd);

//? ------------------------------------------------------------------------ */
//?                               error_messages                             */
//? ------------------------------------------------------------------------ */

void		invalid_option(char *cmd, char *option);
void		invalid_identifier(char *cmd, char *arg);
int			msg_parsing_error(char *input);
int			msg_command_not_found(t_cmd **cmd);

//? ------------------------------------------------------------------------ */
//?                                    utils                                 */
//? ------------------------------------------------------------------------ */

int			ft_isbuiltin(t_cmd *cmd);
int			ft_key_only_snake(char *s);
int			ft_close(int fd);
int			ft_close_pipes(t_pipe pipes);

/* -------------------------------------------------------------------------- */
/*                                   parser                                   */
/* -------------------------------------------------------------------------- */

char		*phase1(char *in, t_enviroment *enviroment);
char		*phase2(char *in, t_enviroment *enviroment);
int			load_commands(t_enviroment *enviroment, char *in);
char		**split_args(char *cmd, t_enviroment *enviroment, int struct_i);
void		pathfinder(t_enviroment *enviroment);
void		execute_cmds(t_cmd **cmd, t_enviroment *enviroment);
int			ft_parsing_error(char *s);

//? ------------------------------------------------------------------------ */
//?                                  execute                                 */
//? ------------------------------------------------------------------------ */

int			run_builtin(t_cmd *cmd, t_enviroment *enviroment);

//? ------------------------------------------------------------------------ */
//?                               manage_files                               */
//? ------------------------------------------------------------------------ */

int			read_here_doc(char *delimiter, int to_fd);
int			read_from_to(int from_fd, int to_fd);
void		fill_output_files(t_cmd *cmd, t_enviroment *enviroment,
				t_pipe pipes);

#endif /* MINISHELL_H */
