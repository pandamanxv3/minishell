/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:41:49 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/06 18:06:08 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

int	is_str_only_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	print_error(char *msg1, char *msg2, char *msg3)
{
	if (msg1)
		write(2, msg1, ft_strlen(msg1));
	if (msg2)
		write(2, msg2, ft_strlen(msg2));
	if (msg3)
	{
		write(2, msg3, ft_strlen(msg3));
		write(2, "\n", 1);
	}
}

void	ft_exit(int i)
{
	int	new_exit;

	new_exit = 0;
	if (g_shell.nb_proc == 1)
		write(2, "exit\n", 5);
	if (g_shell.tab_proc[i].nb_tokens > 1)
	{
		if (is_str_only_num(g_shell.tab_proc[i].tab_token[1].word) == 1)
		{
			new_exit = ft_atoi(g_shell.tab_proc[i].tab_token[1].word);
			if (g_shell.tab_proc[i].nb_tokens > 2)
			{
				print_error("exit: ", "too many arguments\n", NULL);
				return ;
			}
		}
		else
			print_error("exit: ", g_shell.tab_proc[i].tab_token[1].word,
				": numeric argument required\n");
	}
	ft_free(g_shell.gc);
	ft_free(g_shell.gc2);
	exit (new_exit);
}
