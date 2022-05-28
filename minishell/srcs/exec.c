/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:57:18 by aboudjel          #+#    #+#             */
/*   Updated: 2022/05/28 07:02:00 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

// void	ft_create_pipe(int in, int out)
// {
// 	int	pipe_fd[2];

// 	pipe_fd[1] = in;
// 	pipe_fd[0] = out;
// 	if (pipe(pipe_fd) == -1)
// 		write(2, "pipe pas marcher\n", 17); // gerer error
// }

// void	ft_dup(int oldfd, int newfd)
// {
// 	if (oldfd == newfd) // essayer denlever le if dentree dans la fonction
// 		return;
// 	if (dup2(oldfd, newfd) == -1)
// 		write(2, "dup2 pas marcher\n", 17); //gerer error
// 	close(oldfd);
// 	return;
// }
// //---------------------------------------------------//
// // char	**get_cmd(int i)
// // {
// // 	char	**tab;

// // 	while(g_shell.tab_proc[i].tab_token->type)
// // }
// //---------------------------------------------------//
// char	*ft_strjoin_and_replace(char *s1, char *s2)
// {
// 	char	*dst;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
// 	if (!dst)
// 	{
// 		if (s1)
// 			free(s1);
// 		return (NULL);
// 	}
// 	while (s1 && s1[i])
// 	{
// 		dst[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		dst[i + j] = s2[j];
// 		j++;
// 	}
// 	dst[i + j] = '\0';
// 	if (s1)
// 		free(s1);
// 	return (dst);
// }
// void	ft_error(char *msg)
// {

// 	perror(msg);
// 	ft_free(g_shell.gc);
// 	ft_free(g_shell.gc2);
// 	exit(1);
// }
// static char	*findpath(char *cmd, char **splitpath)
// {
// 	int		returnvalue;
// 	int		i;
// 	char	*path;

// 	path = NULL;
// 	i = 0;
// 	if (!splitpath)
// 		return(path);
// 	path = ft_strjoin_and_replace(path, cmd);
// 	if (!path)
// 		ft_error("error malloc ft_strjoin");
// 	returnvalue = access(path, F_OK);
// 	while (returnvalue == -1 && splitpath && splitpath[i])
// 	{
// 		path = ft_strjoin_and_replace(splitpath[i], "/");
// 		if (!path)
// 			ft_error("error malloc ft_strjoin");
// 		path = ft_strjoin_and_replace(path, cmd);
// 		if (!path)
// 			ft_error("error malloc ft_strjoin");
// 		returnvalue = access(path, F_OK);
// 		i++;
// 	}
// 	return (path);
// }

// static char	*extractpath(void)
// {
// 	t_env	*tmp;

// 	tmp = g_shell.lst_env;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->val, "PATH", 4))
// 			return (tmp->var);
// 		tmp = tmp->next;
// 	}
// 	return(NULL);
// }

// char	*getpath(char *cmd)
// {
// 	char 	*path;
// 	char	**splitpath;
// 	path = extractpath();
// 	splitpath = ft_dispatchsplit(path, ':', g_shell.gc2);
// 	path = findpath(path, splitpath);
// 	ft_gcadd_back(g_shell.gc2, ft_gcnew(path,g_shell.gc2));
// 	return (path);
// }

// char	**get_envtab(void)
// {
// 	char 	**tab;
// 	t_env	*tmp;
// 	char	*str;
// 	int		i;

// 	tmp = g_shell.lst_env;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	tab = malloc(sizeof(char *) * i + 1);
// 	if (!tab)
// 		ft_error("error malloc get_env failed");
// 	tab[i] = '\0';
// 	i = 0;
// 	tmp = g_shell.lst_env;
// 	while (tmp)
// 	{
// 		str = ft_strjoin(tmp->var, "=");
// 		if (!str)
// 		{
// 			free(tab);
// 			ft_error("error malloc ft_strjoin get_env failed");
// 		}
// 		tab[i] = ft_strjoin(str, tmp->val);
// 		if (!tab[i])
// 			ft_error("error malloc ft_strjoin 2 get_env failed");
// 		ft_gcadd_back(g_shell.gc2, ft_gcnew(tab[i],g_shell.gc2));
// 		free(str);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	ft_gcadd_back(g_shell.gc2, ft_gcnew(tab,g_shell.gc2));
// 	return (tab);
// }

// char	**get_commandtab(int i)
// {
// 	char	**tab;
// 	int		count;
// 	int		j;

// 	j = 0;
// 	count = 0;
// 	while (j < g_shell.tab_proc[i].nb_tokens)
// 	{
// 		if (g_shell.tab_proc[i].tab_token[j].type == BUILTIN || g_shell.tab_proc[i].tab_token[j].type == COMMAND
// 			|| g_shell.tab_proc[i].tab_token[j].type == WORD || g_shell.tab_proc[i].tab_token[j].type == WORD_N)
// 			count++;
// 		j++;
// 	}
// 	if (count == 0)
// 		return(NULL);
// 	tab = malloc(sizeof(char *) * count + 1);
// 	if (!tab)
// 		ft_error("malloc get_command failed");
// 	tab[count] = '\0';
// 	ft_gcadd_back(g_shell.gc2, ft_gcnew(tab,g_shell.gc2));
// 	j = 0;
// 	count = 0;
// 	while (j < g_shell.tab_proc[i].nb_tokens)
// 	{
// 		if (g_shell.tab_proc[i].tab_token[j].type == BUILTIN || g_shell.tab_proc[i].tab_token[j].type == COMMAND
// 			|| g_shell.tab_proc[i].tab_token[j].type == WORD || g_shell.tab_proc[i].tab_token[j].type == WORD_N)
// 		{
// 			tab[count] = g_shell.tab_proc[i].tab_token[j].word;
// 			count ++;
// 		}
// 		j++;
// 	}
// 		return (tab);
// }
// //---------------------------------------------------//

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
		write(1, ">", 1);
		tmp = get_next_line(0);
		if (val_strncmp(tmp, limiter, size) == 0)
			break;
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	free(tmp);
	close(fd);
	fd = ft_open("./temp/heredoc.tmp", O_RDONLY);
	return (fd);
}

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
		write(2, "\n", 1); //FAUT QUITTER LA
		return (-1);
	}
	if (fd < 0 && (type == 1 || type == 2))
	{
		write(2, "couldn't open or create: ", 25); //perror etc
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
			if (g_shell.tab_proc[i].in_fd != STDIN_FILENO) //ca quit, a ajouter, genre ca quite vraiment partout meme si builtin et nb_process == 1 mais la ca exit jsais pas pq
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
			// ft_free(g_shell.gc2); si leak lors du fail dopen, mais peur de free la global partout
			// ft_free(g_shell.gc);
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
	exec_fd(i, 0);
	if (i < g_shell.nb_proc	- 1)
		close(g_shell.tab_proc[i + 1].in_fd);
	if (g_shell.tab_proc[i].in_fd != STDIN_FILENO)
	ft_dup(g_shell.tab_proc[i].in_fd, STDIN_FILENO);
	if (g_shell.tab_proc[i].out_fd != STDOUT_FILENO)
	ft_dup(g_shell.tab_proc[i].out_fd, STDOUT_FILENO);
	while ((g_shell.tab_proc[i].tab_token[j].type != BUILTIN && g_shell.tab_proc[i].tab_token[j].type != COMMAND)
		&& j < g_shell.tab_proc[i].nb_tokens)
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
			if (g_shell.tab_proc[i].tab_token[j].word)
				write(2, "command not found: ", 19);
			else
				write(2, "permission denied:", 18);
			write(2, g_shell.tab_proc[i].tab_token[j].word, ft_strlen(g_shell.tab_proc[i].tab_token[j].word));
			write(2, "\n", 1); //free
			ft_free(g_shell.gc2);
			ft_free(g_shell.gc);
			exit (1);
		}
}

void	dispatch_exec(void)
{
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
			while (j < g_shell.tab_proc[i].nb_tokens && g_shell.tab_proc[i].tab_token[j].type != BUILTIN)
				j++;
			if (j < g_shell.tab_proc[i].nb_tokens && g_shell.tab_proc[i].tab_token[j].type == BUILTIN)
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