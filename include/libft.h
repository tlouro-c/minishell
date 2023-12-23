/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:51:39 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/23 12:05:56 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define HEX 16
# define OCT 8
# define BIN 2

# define FALSE 0
# define TRUE 1

typedef int	t_bool;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

/* -------------------------------------------------------------------------- */
/*                            FT_PRINTF_STRUCTURES                            */
/* -------------------------------------------------------------------------- */

typedef struct s_inc
{
	size_t	i;
	size_t	written;
}	t_inc;

typedef struct s_flags_c_p
{
	int		width;
	t_bool	hifen;
	t_bool	zero;
}	t_flags_c_p;

typedef struct s_flags_s
{
	int		width;
	int		precision;
	t_bool	precision_on;
	t_bool	hifen;
	t_bool	zero;
}	t_flags_s;

typedef struct s_flags_x
{
	int		width;
	int		precision;
	t_bool	precision_on;
	t_bool	hifen;
	t_bool	zero;
	t_bool	hash;
	t_bool	upper_case;
}	t_flags_x;

typedef struct s_flags_i_d
{
	int		width;
	int		precision;
	t_bool	precision_on;
	t_bool	hifen;
	t_bool	zero;
	t_bool	plus;
	t_bool	space;
	t_bool	written_minus;
}	t_flags_i_d;

typedef struct s_flags_u
{
	int		width;
	int		precision;
	t_bool	precision_on;
	t_bool	hifen;
	t_bool	zero;
}	t_flags_u;

/* -------------------------------------------------------------------------- */
/*                            "ft_print" functions                            */
/* -------------------------------------------------------------------------- */

int				ft_printf(const char *format, ...);

void			action(const char *format, va_list *args, t_inc *incrementors);
char			find_specifier(const char *format, t_inc *incrementors);
t_bool			isflag(char c);
int				apply_c(const char *format, va_list *args, int pos);
int				apply_s(const char *format, va_list *args, int pos);
int				apply_p(const char *format, va_list *args, int pos);
int				apply_x(const char *format, va_list *args, int pos,
					char specifier);
int				apply_i_d(const char *format, va_list *args, int pos);
int				apply_u(const char *format, va_list *args, int pos);
int				write_c_x_times(char c, int x);
void			alloc_error_exit(int error_value, va_list *args);
int				number_len(int number);
int				number_len_u(unsigned int number);
int				hexa_len(unsigned long n, int base_size, char *base);
int				ft_putnbr_bases(unsigned long n, int base_size, char *base);
int				invalid_specifier_or_special(char specifier, va_list *args);
void			putnbr_d_i(long n);
int				quick_edge(int n, t_flags_i_d flags);

/* -------------------------------------------------------------------------- */
/*                               "is" functions                               */
/* -------------------------------------------------------------------------- */

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isspace(int c);
int				ft_isspace(int c);

/* -------------------------------------------------------------------------- */
/*                               "to" functions                               */
/* -------------------------------------------------------------------------- */

int				ft_tolower(int c);
int				ft_toupper(int c);

/* -------------------------------------------------------------------------- */
/*                              "utils" functions                             */
/* -------------------------------------------------------------------------- */

unsigned int	ft_rand(void);
void			ft_swap(int *a, int *b);
int				ft_abs(int n);
char			*ft_itoa(int value, char *buffer, int base);
int				ft_atoi(const char *s);
long			ft_atol(const char *s);
long long		ft_atoll(const char *s);

/* -------------------------------------------------------------------------- */
/*                             "sorting" functions                            */
/* -------------------------------------------------------------------------- */

void			ft_quick_sort(int *array, int size);

/* -------------------------------------------------------------------------- */
/*                             "string" functions                             */
/* -------------------------------------------------------------------------- */

size_t			ft_strlen(const char *s);
char			*ft_strrev(char *s);
char			*ft_strrchr(const char *s, int c);
int				ft_count_words(char const *s, int sep);
char			**ft_split(char const *s, int sep);
int				ft_putstr_fd(char *s, int fd);
int				ft_putchar_fd(int c, int fd);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);

/* -------------------------------------------------------------------------- */
/*                              "free" functions                              */
/* -------------------------------------------------------------------------- */

char			**ft_free_str_arr(char **array, int size);
char			*ft_free_str_return(char *s);

/* -------------------------------------------------------------------------- */
/*                        "ft_get_next_line function"                        */
/* -------------------------------------------------------------------------- */

char			*ft_get_next_line(int fd);
char			*ft_get_next_line_v2(int fd);

/* -------------------------------------------------------------------------- */
/*                               "mem" functions                              */
/* -------------------------------------------------------------------------- */

void			*ft_calloc(size_t count, size_t size);
void			*ft_memset(void *b, int c, size_t len);

/* -------------------------------------------------------------------------- */
/*                              "math" functions                              */
/* -------------------------------------------------------------------------- */

float			ft_rad(float deg);

/* -------------------------------------------------------------------------- */
/*                       "singly_linked_list" functions                       */
/* -------------------------------------------------------------------------- */

t_node			*ft_insert_at_beginning(t_node **list, void *content);
void			ft_print_list(t_node *list, char format_specifier);
void			ft_remove_at_beggining(t_node **list);
void			ft_remove_if(t_node **list, void *ref,
					int (*cmp)(void *content, void *ref));
size_t			ft_list_size(t_node *list);
void			ft_clear_list(t_node **list);

#endif /* LIBFT_H */
