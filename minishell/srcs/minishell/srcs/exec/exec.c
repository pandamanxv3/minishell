/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:57:18 by aboudjel          #+#    #+#             */
/*   Updated: 2022/05/31 20:00:47 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

static int copy_var_hd(char *copy, char *str)
{
	int		j;
	int		k;
	t_env	*temp;
	
	g_shell.index_hd++;
		if (str[g_shell.index_hd] && (ft_isalpha(str[g_shell.index_hd]) == 1 
			|| str[g_shell.index_hd] == '_' || str[g_shell.index_hd] == '?'))
		j = g_shell.index_hd;
	else
	{
		copy[0] = '$';
		return (1);		
	}
	if (str[g_shell.index_hd++] == '?')
		return (itoa_remixed(copy));

	while ((ft_isalnum(str[g_shell.index_hd]) == 1 || str[g_shell.index_hd] == '_') && str[g_shell.index_hd])
		g_shell.index_hd++;
	printf(" ft_gestion_var index = %c %d\n", str[g_shell.index_hd], g_shell.index_hd);
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.index_hd - j));

		if (k == 0)
		{
			k = ft_strlen(temp->val);
			val_strlcpy(copy, temp->val, k);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

static int	gestion_var_size_hd(int j, int k, char *str)
{
	t_env	*temp;

	g_shell.index_hd++;
	j = g_shell.index_hd;
	if (str[g_shell.index_hd] == '?')
		return (size_error());
	if (ft_isalpha(str[g_shell.index_hd]) == 0
		&& str[g_shell.index_hd] != '_')
		return (1);
	g_shell.index_hd++;
	while (ft_isalnum(str[g_shell.index_hd]) == 1
		|| str[g_shell.index_hd] == '_')
		g_shell.index_hd++;
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.index_hd - j));
		if (k == 0)
		{
			k = ft_strlen(temp->val);
			return (k);
		}
		temp = temp->next;
	}
	return (0);
}

static char	*heredoc_replace(char *tmp)
{
	char *dst;
	int count;

	count = 0;
	g_shell.index_hd = 0;
	while(tmp[g_shell.index_hd])
	{
		if (tmp[g_shell.index_hd] == '$')
			count += gestion_var_size_hd(0, 0, tmp);
		else
		{
			count++;
			g_shell.index_hd++;
		}
	}
	dst = malloc(sizeof(char) * count + 1);
	if (!dst)
		ft_error("error : malloc problem in the heredoc");
	dst[count] = '\0';
	g_shell.index_hd = 0;
	count = 0;
	while(tmp[g_shell.index_hd])
	{
		if (tmp[g_shell.index_hd] == '$')
			count += copy_var_hd(dst + count, tmp);
		else
			dst[count++] = tmp[g_shell.index_hd++];
	}
	free(tmp);
	return (dst);
}

int	ft_heredoc(char *limiter)
{
	char	*tmp;
	int		fd;
	int		size;

	size = ft_strlen(limiter);
	fd = open("./temp/heredoc.tmp", O_TRUNC | O_APPEND
			| O_CREAT | O_RDWR, 0000644);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || !val_strncmp(tmp, limiter, size))
			break ;
		if(ft_strchr(tmp, '$'))
			tmp = heredoc_replace(tmp);
		// printf("tmp:%s\n", tmp);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
		free(tmp);
	}
	free(tmp);
	close(fd);
	fd = ft_open("./temp/heredoc.tmp", O_RDONLY);
	return (fd);
}

// int	ft_heredoc(char *limiter)
// {
// 	char	*tmp;
// 	int		fd;
// 	int		size;

// 	size = ft_strlen(limiter);
// 	fd = open("./temp/heredoc.tmp", O_TRUNC | O_APPEND
// 			| O_CREAT | O_RDWR, 0000644);
// 	while (1)
// 	{	
// 		write(1, ">", 1);
// 		tmp = get_next_line(0);
// 		if (val_strncmp(tmp, limiter, size) == 0)
// 			break;
// 		if(ft_strchr(tmp, '$'))
// 			tmp = heredoc_replace(tmp);
// 		printf("tmp:%s\n", tmp);
// 		write(fd, tmp, ft_strlen(tmp));
// 		free(tmp);
// 	}
// 	free(tmp);
// 	close(fd);
// 	fd = ft_open("./temp/heredoc.tmp", O_RDONLY);
// 	return (fd);
// }

int		ft_open(char *str, int type)
{
	int fd;

	if (type == 0)
		fd = open(str, O_RDONLY);
	if (type == 1)
		fd = open(str, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (type == 2)
		fd = open(str, O_APPEND | O_CREAT | O_RDWR, 0000644);
	if (fd < 0 && type == 0)
	{
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory", 27);
		write(2, "\n", 1);
		return (-1);
	}
	if (fd < 0 && (type == 1 || type == 2))
	{
		write(2, "couldn't open or create: ", 25);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	return (fd);
}

void	exec_fd(int i, int child_or_parents)
{
	int j;

	j = 0;
	while (j < g_shell.tab_proc[i].nb_tokens)
	{
		if (g_shell.tab_proc[i].tab_token[j].type == INFILE)
		{
			if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
				close(g_shell.tab_proc[i].in_fd);
			g_shell.tab_proc[i].in_fd = ft_open(g_shell.tab_proc[i].tab_token[j].word, 0);
			if (g_shell.tab_proc[i].in_fd < 0)
			{
				if (child_or_parents == 1)
					return;
				else
				{
					ft_free(g_shell.gc2);
					ft_free(g_shell.gc);
					exit(1);
				}				
			}
		}
		else if (g_shell.tab_proc[i].tab_token[j].type == OUTFILE)
		{
			if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
				close(g_shell.tab_proc[i].out_fd);
			g_shell.tab_proc[i].out_fd = ft_open(g_shell.tab_proc[i].tab_token[j].word,	1);
		}
		else if (g_shell.tab_proc[i].tab_token[j].type == HEREDOC)
		{
			if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
				close(g_shell.tab_proc[i].in_fd);
			g_shell.tab_proc[i].in_fd = ft_heredoc(g_shell.tab_proc[i].tab_token[j].word);
		}
		else if(g_shell.tab_proc[i].tab_token[j].type == OUTFILE_APPEND)
		{
			if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
				close(g_shell.tab_proc[i].out_fd);
			g_shell.tab_proc[i].out_fd = ft_open(g_shell.tab_proc[i].tab_token[j].word, 2);
		}
		j++;
		if (g_shell.tab_proc[i].in_fd < 0 || g_shell.tab_proc[i].out_fd < 0)
		{
			if (g_shell.tab_proc[i].in_fd > 0)
				close(g_shell.tab_proc[i].in_fd);
			if (g_shell.tab_proc[i].out_fd > 1)
				close(g_shell.tab_proc[i].out_fd);
			ft_free(g_shell.gc2);
			ft_free(g_shell.gc);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_close(int i)
{
	if (g_shell.tab_proc[i].in_fd != 0)
		close(g_shell.tab_proc[i].in_fd);
	if (i != g_shell.nb_proc - 1)
		close(g_shell.tab_proc[i].out_fd);
}

void	child(int i)
{
	int	j;

	j = 0;
	puts("coucou from child");
	exec_fd(i, 0);
	if (i < g_shell.nb_proc	- 1)
		close(g_shell.tab_proc[i + 1].in_fd);
	if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
	ft_dup(g_shell.tab_proc[i].in_fd, STDIN_FILENO);
	if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
	ft_dup(g_shell.tab_proc[i].out_fd, STDOUT_FILENO);
	while (j < g_shell.tab_proc[i].nb_tokens && (g_shell.tab_proc[i].tab_token[j].type != BUILTIN && g_shell.tab_proc[i].tab_token[j].type != COMMAND))
		j++;
	// ft_close(i);
	if (j < g_shell.tab_proc[i].nb_tokens && g_shell.tab_proc[i].tab_token[j].type == BUILTIN)
    {
		builtin_share(i, j);
		ft_free(g_shell.gc2);
		ft_free(g_shell.gc);
        exit (0);
    }
	if (j < g_shell.tab_proc[i].nb_tokens && g_shell.tab_proc[i].tab_token[j].type == COMMAND)
		if (execve(getpath(g_shell.tab_proc[i].tab_token[j].word), get_commandtab(i), get_envtab()) == -1) 
		{
			if (g_shell.tab_proc[i].tab_token[j].word[0])
				write(2, "command not found: ", 19);
			else
				write(2, "permission denied:", 18);
			write(2, g_shell.tab_proc[i].tab_token[j].word, ft_strlen(g_shell.tab_proc[i].tab_token[j].word));
			write(2, "\n", 1);
			ft_free(g_shell.gc2);
			ft_free(g_shell.gc);
			exit (1);
		}
}

void	dispatch_exec(void)
{
	// print_env(g_shell.lst_env);
	int	i;
	int j;
	int save_in;
	int	save_out;
	j = 0;
	i = 0;
	g_shell.pid = ft_malloc("int", g_shell.nb_proc, "error malloc pid", g_shell.gc2);
	while (i < g_shell.nb_proc)
	{
		if (g_shell.nb_proc > 1 && i < g_shell.nb_proc - 1)
			ft_create_pipe(i);
		if (g_shell.nb_proc == 1)
		{
			while (j < g_shell.tab_proc[i].nb_tokens - 1 && g_shell.tab_proc[i].tab_token[j].type != BUILTIN  && g_shell.tab_proc[i].tab_token[j].type != COMMAND)
			{
				printf("type :%d\n", g_shell.tab_proc[i].tab_token[j].type);
				j++;
			}
			printf("type :%d\n", g_shell.tab_proc[i].tab_token[j].type);
			if (g_shell.tab_proc[i].tab_token[j].type != COMMAND) // pour que si ya r ni lun ni lautre ca rentre quand meme dans le cas ou ya juste un outfile/infile sinn ca allait dans le child
			{
				exec_fd(i, 1);
				if (g_shell.tab_proc[i].in_fd >= 0)
				{
					if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
					{
						save_in = dup(STDIN_FILENO);
						dup2(g_shell.tab_proc[i].in_fd, STDIN_FILENO);
					}
					if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
					{
						save_out = dup(STDOUT_FILENO);
						dup2(g_shell.tab_proc[i].out_fd, STDOUT_FILENO);
					}
					if (g_shell.tab_proc[i].tab_token[j].type == BUILTIN)
						builtin_share(i, j);
					if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
						dup2(save_in, STDIN_FILENO);
					if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
						dup2(save_out, STDOUT_FILENO);
				}
				return ;
			}
		}
		g_shell.pid[i] = fork();
		if (g_shell.pid[i] < 0)
			return; //gestion error
		if (g_shell.pid[i] > 0)
		ft_close(i);
		if (g_shell.pid[i] == 0)
			child(i);	
		i++;
	}
	i = 0; 
	while(i < g_shell.nb_proc)
		waitpid(g_shell.pid[i++], NULL, 0); //stocker avec un wait la valeur de retour de ce dernier qui va correspondre a la sortie d'exit du dernier process
	printf("****************************************\n");
} // si juste un builtin pas de fork, si plusieurs bultin ou builtin/commande faire les builtin dans les fork et ils vont etre useless
// valgrind --suppressions=readline_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./minishell