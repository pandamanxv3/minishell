/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:04:32 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/02 11:58:21 by cbarbit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	val_strlcpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return ;
}

static int copy_var(char *copy, int i, char *str)
{
	int		j;
	int		k;
	t_env	*temp;
	
	g_shell.tab_proc[i].index++;
	if (str[g_shell.tab_proc[i].index] && (ft_isalpha(str[g_shell.tab_proc[i].index]) == 1 
		|| str[g_shell.tab_proc[i].index] == '_' || str[g_shell.tab_proc[i].index] == '?'))
		j = g_shell.tab_proc[i].index;
	else
	{
		copy[0] = '$';
		return (1);		
	}
	if (str[g_shell.tab_proc[i].index++] == '?')
		return (itoa_remixed(copy));
	while ((ft_isalnum(str[g_shell.tab_proc[i].index]) == 1 || str[g_shell.tab_proc[i].index] == '_') && str[g_shell.tab_proc[i].index])
		g_shell.tab_proc[i].index++;
	temp = g_shell.lst_env;
	while (temp)
	{
		k = val_strncmp((str + j), temp->var, (g_shell.tab_proc[i].index - j));

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

// static int copy_var(char *copy, int i, char *str)
// {
// 	int		j;
// 	int		k;
// 	t_env	*temp;
	
// 	g_shell.tab_proc[i].index++;
// 	if (str[g_shell.tab_proc[i].index] == '\0')
// 	{
// 		copy[0] = '$';
// 		return (1);		
// 	}
// 	j = g_shell.tab_proc[i].index;
// 	if (str[g_shell.tab_proc[i].index++] == '?')
// 		return (itoa_remixed(copy));
// 	if (!str[g_shell.tab_proc[i].index + 1] && (ft_isalpha(str[g_shell.tab_proc[i].index]) == 1 && str[g_shell.tab_proc[i].index] != '_'))
// 	{
// 		copy[0] = '$';
// 		return (1);
// 	}
// 	while (str[g_shell.tab_proc[i].index] && (ft_isalnum(str[g_shell.tab_proc[i].index]) == 1 || str[g_shell.tab_proc[i].index] == '_'))
// 		g_shell.tab_proc[i].index++;
// 	temp = g_shell.lst_env;
// 	while (temp)
// 	{
// 		k = val_strncmp((str + j), temp->var, (g_shell.tab_proc[i].index - j));

// 		if (k == 0)
// 		{
// 			k = ft_strlen(temp->val);
// 			val_strlcpy(copy, temp->val, k);
// 			return (k);
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }


static void copy_on_simple_quote(int	i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '\'')
	{
		g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count++] = str[g_shell.tab_proc[i].index++];
	}
	g_shell.tab_proc[i].index++;
}

static void	copy_on_double_quote(int i, int j, char *str)
{
	g_shell.tab_proc[i].index++;
	while (str[g_shell.tab_proc[i].index] != '"')
	{
		if (str[g_shell.tab_proc[i].index] == '$')
			g_shell.tab_proc[i].tab_token[j].word_malloc_count += copy_var(g_shell.tab_proc[i].tab_token[j].word + g_shell.tab_proc[i].tab_token[j].word_malloc_count, i, str);
		else
		{
			g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count++] = str[g_shell.tab_proc[i].index++];
		}
	}
	g_shell.tab_proc[i].index++;
}

void	copy_token(int i, int j, char *str)
{
	g_shell.tab_proc[i].tab_token[j].word_malloc_count = 0;
	while (str[g_shell.tab_proc[i].index] == ' ')
		g_shell.tab_proc[i].index++;
	if (str[g_shell.tab_proc[i].index] == '>' || str[g_shell.tab_proc[i].index] == '<')
	{
		while (str[g_shell.tab_proc[i].index] == '>' || str[g_shell.tab_proc[i].index] == '<')
			g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count++] = str[g_shell.tab_proc[i].index++];
		g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count] = '\0';
		return ;
	}
	while(str[g_shell.tab_proc[i].index] && str[g_shell.tab_proc[i].index] != ' '
		&& str[g_shell.tab_proc[i].index] != '<' && str[g_shell.tab_proc[i].index] != '>')
	{
		if (str[g_shell.tab_proc[i].index] == '$')
		{
			//printf("STRING STR: %s\n", str);
			g_shell.tab_proc[i].tab_token[j].word_malloc_count += copy_var(g_shell.tab_proc[i].tab_token[j].word + g_shell.tab_proc[i].tab_token[j].word_malloc_count, i, str);
			//g_shell.tab_proc[i].tab_token[j].word_malloc_count += copy_var(g_shell.tab_proc[i].tab_token[j].word, i, str);
			//printf("WORD: %s\n", g_shell.tab_proc[i].tab_token[j].word);
			//printf("MALLLOC_WORD: %d\n", g_shell.tab_proc[i].tab_token[j].word_malloc_count);	
		}
		else if (str[g_shell.tab_proc[i].index] == '"')
            copy_on_double_quote(i, j, str);
		else if (str[g_shell.tab_proc[i].index] == '\'')
            copy_on_simple_quote(i, j, str);
		else
            g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count++] = str[g_shell.tab_proc[i].index++];		
	}
	g_shell.tab_proc[i].tab_token[j].word[g_shell.tab_proc[i].tab_token[j].word_malloc_count] = '\0';
//	printf(" count %d\n", g_shell.tab_proc[i].tab_token[j].word_malloc_count);
//	printf("STRING3 %s\n", g_shell.tab_proc[i].tab_token[j].word);
	return ;
}