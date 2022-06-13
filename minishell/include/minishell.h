/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:09:51 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/13 18:11:38 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBRARIES */

# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h> 
# include <limits.h>
# include "../libft/include/libft.h"

/* DEFINED VARIABLES */

# define MINISHELL "minishell>"

/* TOKEN STRUCTURE */

typedef struct s_token
{
	char	*word;
	int		type;
	int		word_malloc_count;
}	t_token;

/* PROCESS DATA STRUCTURE */

typedef struct s_process
{
	char	*str;
	int		strlen;
	int		start;
	int		end;
	int		index;
	char	*path;
	int		in_fd;
	int		out_fd;
	int		hd_fd[1024];
	int		nb_tokens;
	t_token	*tab_token;
}	t_process;

/* TOKEN TYPES */

typedef enum e_toke_types
{
	BUILTIN,
	COMMAND,
	WORD,
	INFILE,
	HEREDOC,
	OUTFILE,
	OUTFILE_APPEND,
	SEPARATOR,
	WORD_N,
}	t_token_types;

/* MAIN STRUCTURE */

typedef struct s_minishell
{
	int			nb_proc;
	char		*line;
	int			length_line;
	int			index_hd;
	int			is_in_hd;
	int			in_prog;
	int			tab_index_pipes[512];
	pid_t		*pid;
	int			error;
	int			unset_pwd;
	char		*temp_old_dir;
	char		*pwd;
	int			save_in;
	t_gc		*gc;
	t_gc		*gc2;
	t_env		*lst_env;
	t_process	*tab_proc;
}	t_minishell;

/* MALLOCS */

int		malloc_processes(void);
int		malloc_tokens(int i, int j);
void	size_malloc_tokens(int i, int j, char *str);

/* SIGNALS */

void	sighandler_int(int signum);
void	sighandler_quit(int signum);

/* LEXER & PARSER */

int		find_nb_proc(void);
int		lexer_prompt(void);
int		init_processes(void);
int		gestion_var_size(int j, int k);
int		val_strncmp(char *stra, char *val, int length);
int		parsing_prompt(void);
void	size_expand(int i, int count);
int		lexer_quote_and_pipe(int i, int k);
int		setup_copy_var(char *copy);

/* TOKENS */

int		init_tokens(void);
void	find_nb_tokens(int j, int i);
void	all_token_types(int i, int j);
void	copy_token(int i, int j, char *str);
void	val_strlcpy(char *dst, char *src, int size);
void	file_types(int i, int j, int r);
int		size_error(void);
int		itoa_remixed(char *dst);
int		is_separator(int i, int j);
int		is_builtin(int i, int j);

/* ENV */

void	add_env(t_env *env, t_env *to_add);
char	*env_dup(char *src, int size, t_gc *gc);
t_env	*get_envlst(char *var, t_gc *gc);
t_env	*get_env(char **env, t_gc *gc);
int		read_env(char *word, int i);
void	replace_env(char *word, int i);

/* BUILTINS */

void	ft_export(char *word);
void	ft_echo(int i, int n, int space);
void	unset(char *str);
void	print_env(t_env *env);
void	ft_pwd(void);
void	ft_chdir(char *path);
void	builtin_share(int i, int j);
void	ft_exit(int i, int new_exit);
void	read_and_replace_env_cd(char *var, char *val);
char	*get_home_val(void);

/* MAIN FUNCS*/

void	minishell(int i);

/* REDIRECTIONS */

int		ft_open(char *str, int type);
char	*new_enumerated_empty_file(char *prefix, int sequence);
int		is_file_created_successfully(char *file_name);
void	dispatch_here_doc(int i, int j);
char	*heredoc_replace(char *tmp, int count, int count2);
void	ft_heredoc(char *limiter, int i);
void	ft_close(int i);

/* EXECUTION */

void	exec_fd(int i, int child_or_parents, int j);
void	dispatch_exec(int i, int j);
void	child(int i);

/* UTILS EXECUTION */

void	ft_dup(int oldfd, int newfd);
void	ft_create_pipe(int i);
char	*getpath(char *cmd);
char	**get_envtab(void);
char	**get_commandtab(int i);
void	ft_error(char *msg);
void	print_error(char *msg1, char *msg2, char *msg3);
void	ft_wait(void);
char	*ft_strjoin_and_replace(char *s1, char *s2, int i);

#endif
