/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:39:42 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/01/13 21:45:26 by tlouro-c         ###   ########.fr       */
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

# ifndef PIPE_BUF
#  define PIPE_BUF 512
# endif

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
# define SPACE2 17
# define S_QUOTE 5
# define D_QUOTE 6
# define RED_RIGHT 14
# define RED_LEFT 15
# define NULL_BYTE 16
# define EMPTY 9

# define READ_END 0
# define WRITE_END 1

# define RESET "\x1B[0m"
# define CYAN "\033[1m\033[36m"
# define MAGENTA "\033[1m\033[35m"

// signal
# define MAIN 42
# define MAIN2 43
# define CHILD 007
# define IGN 777

typedef struct s_pipe
{
	int	pipes[2];
	int	input_pipe[2];
	int	input_for_next;
	int	fd_in;
	int	fd_out;
}	t_pipe;

typedef struct s_cmd
{
	char	**args;
	int		priorities;
	char	*input_file;
	int		if_notfirst;
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
	pid_t			*child_pid;
	int				stdin_fd;
	int				stdout_fd;
	unsigned int	status;
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
void		define_prompt(t_enviroment *enviroment);

//? ------------------------------------------------------------------------ */
//?                                  signals                                 */
//? ------------------------------------------------------------------------ */

void		setup_signals(int n);
void		handle_sigint_main(int sig);
void		handle_sigint_main2(int sig);
void		set_up_main_signals(struct sigaction *sa, int n);

//? ------------------------------------------------------------------------ */
//?                                  built_ins                               */
//? ------------------------------------------------------------------------ */

int			cmd_pwd(void); // ✅
int			cmd_env(char **args, t_list *variables); // ✅
int			cmd_echo(char **args); // ✅
void		cmd_exit(char **args, t_enviroment *enviroment, t_pipe *pipes);
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
int			ft_keylen(const char *key);
char		*get_env_declare(char *enviroment_variable);

//? ------------------------------------------------------------------------ */
//?                                  exit_utils                              */
//? ------------------------------------------------------------------------ */

void		error_allocating_memory(t_enviroment *enviroment);
void		error_piping(t_enviroment *enviroment);
void		error_and_close_pipes(t_enviroment *enviroment, t_pipe *pipes);
void		error_allocating_memory_free_str(t_enviroment *enviroment, char *s);
void		error_allocating_memory_free_arr(t_enviroment *enviroment,
				void **arr);
void		free_enviroment(t_enviroment *enviroment);
void		free_cmds(t_enviroment *enviroment);
void		free_exit(t_enviroment *enviroment, int status);
void		free_cmd(t_enviroment *enviroment, int i);
void		ft_free(void **ptr);

//? ------------------------------------------------------------------------ */
//?                               error_messages                             */
//? ------------------------------------------------------------------------ */

void		invalid_option(char *cmd, char *option);
void		invalid_identifier(char *cmd, char *arg);
int			msg_parsing_error(char *input, t_enviroment *enviroment);
int			msg_command_not_found(t_cmd **cmd, t_enviroment *enviroment);
int			msg_cd_error(char **args, int mode);

//? ------------------------------------------------------------------------ */
//?                                    utils                                 */
//? ------------------------------------------------------------------------ */

int			ft_isbuiltin(t_cmd *cmd);
int			ft_key_only_snake(char *s);
int			ft_close(int *fd);
int			ft_close_pipes(t_pipe *pipes);
void		innit_pipes(t_pipe *pipes);
void		set_pwd(t_enviroment *enviroment);
void		set_oldpwd(t_enviroment *enviroment);
int			echo_strcmp(char *s1);
void		dup2andclose(int *fd1, int fd2);

//? ------------------------------------------------------------------------ */
//?                                  parser                                  */
//? ------------------------------------------------------------------------ */

char		*phase1(char *in, t_enviroment *enviroment);
char		*phase2(char *in, t_enviroment *enviroment);
int			load_commands(t_enviroment *enviroment, char *in);
char		**split_args(char *cmd, t_enviroment *enviroment, int struct_i);
void		pathfinder(t_enviroment *enviroment);
void		execute_cmds(t_cmd **cmd, t_enviroment *enviroment);
int			ft_parsing_error(char *s);
void		swap_input_for_next(t_pipe *pipes, t_enviroment *enviroment, int i);

//? ------------------------------------------------------------------------ */
//?                                  execute                                 */
//? ------------------------------------------------------------------------ */

int			run_builtin(t_cmd *cmd, t_enviroment *enviroment, t_pipe *pipes);
void		wait_loop(t_enviroment *enviroment);
int			check_priorities(t_cmd **cmd, t_enviroment *enviroment, int i);
void		save_std_fds(t_pipe *pipes);

//? ------------------------------------------------------------------------ */
//?                               manage_files                               */
//? ------------------------------------------------------------------------ */

int			read_here_doc(char *delimiter, int to_fd, t_enviroment *enviroment);
int			read_from_to(int from_fd, int to_fd);
void		fill_output_files(t_cmd *cmd, t_enviroment *enviroment,
				t_pipe *pipes);
int			fill_pipes_with_input(t_cmd *cmd, t_enviroment *enviroment,
				t_pipe *pipes);

#endif /* MINISHELL_H */
