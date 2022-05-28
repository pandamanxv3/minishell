/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:30:57 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/28 05:31:26 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_minishell	g_shell;

void	print_env(t_env *env) //env
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		printf("%s", temp->var);
		printf("=");
		printf("%s\n", temp->val);
		if (!temp->next)
			break ;
		temp = temp->next;
	}
}

static int		check_unset(int i, char *str)
{
	int check;

	check = 0;
	if (i == 0 && (ft_isdigit(str[i]) == 1))
		check = 1;
	if ((ft_isalnum(str[i]) == 0 && str[i] != '_'))
		check = 1;
	if (check == 1)
	{
		ft_putstr_fd("unset: `", 2);
		write(2, str, ft_strlen(str));
		ft_putendl_fd("': not a valid identifier", 2);
	}
	return (check);
}
void	unset(char *str)
{
	int	i;
	t_env *temp;

	i = 0;
	if(!str[i])
		return;
	if (val_strncmp(str, "PWD", ft_strlen(str)) && g_shell.unset_pwd != -1)
		g_shell.unset_pwd = 1;
	if (val_strncmp(str, "OLDPWD", ft_strlen(str)))
		g_shell.unset_pwd = -1;
	while (str[i])
	{
		if (check_unset(i, str) == 1)
			return ;
		i++;
	}
	temp = g_shell.lst_env;
	if (val_strncmp(str, g_shell.lst_env->var, ft_strlen(str)) == 0)
		g_shell.lst_env = g_shell.lst_env->next;
	while (temp->next)
	{
		if (val_strncmp(str, temp->next->var, ft_strlen(str)) == 0)
		{
			temp->next = temp->next->next;
			return ;
		}
		temp = temp->next;
	}
}

void	replace_env(char *word, int i)
{
	t_env	*current;

	current = g_shell.lst_env;
	while(current)
	{
		if (val_strncmp(word, current->var, i) == 0)
		{
			current->val = env_dup(word + i + 1, ft_strlen(word + i), g_shell.gc);
			break;
		}
		current = current->next;
	}
}

int	read_env(char *word, int i)
{
	t_env	*current;

	current = g_shell.lst_env;
	while(current)
	{
		if (val_strncmp(word, current->var, i) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}


void	ft_export(char *word) // faut le faire pour chaque fois //renommer ft_export plutot
{
	int	i;

	i = 0;
	while (word[i] && word[i] != '=')
	{
		if ((i == 0 && ft_isdigit(word[i]))
			&& (ft_isalnum(word[i]) == 0 || word[i] != '_'))
		{
			ft_putstr_fd("export: ", 2);
			write(2, word, ft_strlen(word));
			ft_putendl_fd(" not a valid identifier", 2);
			break;
		}
		i++;
	}
	if (word[i] == '=')
	{
		if (read_env(word, i) == 0)
			replace_env(word, i);
		else
			add_env(g_shell.lst_env, get_envlst(word, g_shell.gc));
	}
}

void	ft_echo(int i)
{
	int j;
	int n;
	int type;
    
	j = 0;
	n = 1;
	type = g_shell.tab_proc[i].tab_token[j].type;
	while (type != WORD && j < g_shell.tab_proc[i].nb_tokens)
	{
		if (type == WORD_N)
			n = 0;
		j++;
		if (j < g_shell.tab_proc[i].nb_tokens)
			type = g_shell.tab_proc[i].tab_token[j].type;
	}
	while (j < g_shell.tab_proc[i].nb_tokens)
	{
		if (type == WORD || type == WORD_N)
			printf("%s", g_shell.tab_proc[i].tab_token[j].word);
		j++;
		if (j < g_shell.tab_proc[i].nb_tokens)
			printf(" ");
		if (j < g_shell.tab_proc[i].nb_tokens)
			type = g_shell.tab_proc[i].tab_token[j].type;
	}
	if (n == 1)
		printf("\n");
}

void ft_exit(void)
{
	if (g_shell.nb_proc == 1)
	{
		printf("exit\n");
		free(g_shell.line);
		ft_free(g_shell.gc);
		ft_free(g_shell.gc2); //a voir si je free partout dans les builtin des fork ou que ici
	}
	exit (0);
}