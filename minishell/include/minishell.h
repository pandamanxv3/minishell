/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:09:51 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/02 15:29:53 by cbarbit          ###   ########.fr       */
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
	int		type; //faire un enum pour le type de chaque mot
	int		word_malloc_count;
}	t_token;

/* PROCESS DATA STRUCTURE */

typedef struct	s_process
{
	char	*str;
	int		strlen;
	int		start;
	int		end;
	int		index;
	char	*path; //path de la commande?
	int		in_fd;
	int		out_fd;
	int		nb_tokens;
	t_token	*tab_token;
}	t_process;

/* TOKEN TYPES */

typedef enum	e_toke_types
{
	BUILTIN, //0
	COMMAND, //1
	WORD, //2
	INFILE, //3
	HEREDOC, //4
	OUTFILE, //5
	OUTFILE_APPEND, //6
	SEPARATOR, //7
	WORD_N, //8
}	t_token_types;

/* MAIN STRUCTURE */

typedef struct	s_minishell
{
	//int			exit;
	int			nb_proc; //défini par le nombre de pipes dans la ligne d'entrée
	char		*line;
	int			length_line;
	int			index_hd;
	int			tab_index_pipes[512];
	pid_t		*pid;
	int			error;
	int			unset_pwd;
	char		*temp_old_dir;
	t_gc		*gc; //gc global
	t_gc		*gc2; //gc propre a chaque line de minishell
	t_env		*lst_env; // liste chainee dans laquelle est stockee l'env
	t_process	*tab_proc; //de taille de nb_process
}	t_minishell;

/* MALLOCS */

int		malloc_processes(void);
int		malloc_tokens(int i, int j);
void	size_malloc_tokens(int i, int j, char *str);

/* SIGNALS */

void	sighandler_int(int signum);
void	sighandler_quit(int signum);

/* LEXER & PARSER */

int 	find_nb_proc(void);
int		lexer_prompt(void);
int		init_processes(void);
int 	gestion_var_size(int i, char *str);
int		val_strncmp(char *stra, char *val, int length);
int		parsing_prompt(void);

/* TOKENS */

int 	init_tokens(void);
void	find_nb_tokens(int j);
void	all_token_types(void);
void	copy_token(int i, int j, char *str);
void	val_strlcpy(char *dst, char *src, int size);
int		size_error(void);
int		itoa_remixed(char *dst);

/* ENV */

void	add_env(t_env *env, t_env *to_add);
char	*env_dup(char *src, int size, t_gc *gc);
t_env	*get_envlst(char *var, t_gc *gc);
t_env	*get_env(char **env, t_gc *gc);
int		read_env(char *word, int i);
void	replace_env(char *word, char *word2, int i);

/* BUILTINS */

void	ft_export(char *word);
void	ft_echo(int i);
void	unset(char *str);
void	print_env(t_env *env);
void	ft_pre_pwd(int i, int j);
char	*ft_pwd(void);
void	ft_chdir(char *path);
void    builtin_share(int i, int j);
void 	ft_exit(int i);

/* MAIN FUNCS*/

void	minishell(void);

/* EXECUTION */

void    dispatch_exec(void);
void    child(int i);
void    exec_fd(int i, int child_or_parents);
int     ft_open(char *str, int type);
int     ft_heredoc(char *limiter);

/* UTILS EXECUTION */

void    ft_dup(int oldfd, int newfd);
void    ft_create_pipe(int i);
char	*getpath(char *cmd);
char	**get_envtab(void);
char	**get_commandtab(int i);
void    ft_error(char *msg);
char    *ft_strjoin_and_replace(char *s1, char *s2);

#endif