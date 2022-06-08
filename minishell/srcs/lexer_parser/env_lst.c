/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:31:52 by cbarbit           #+#    #+#             */
/*   Updated: 2022/06/08 05:24:26 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_minishell	g_shell;

void	add_env(t_env *env, t_env *to_add)
{
	t_env	*temp;

	temp = env;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
}

char	*env_dup(char *src, int size, t_gc *gc)
{
	char	*dest;
	int		returnvalue;

	dest = ft_malloc("str", size, "erreur malloc var/val lst_env", gc);
	returnvalue = ft_strlcpy(dest, src, size);
	return (dest);
}

t_env	*get_envlst(char *var, t_gc *gc)
{
	t_env	*lst_env;
	int		i;

	i = 0;
	lst_env = ft_malloc("env", 0, "erreur malloc lst_env", gc);
	while (var[i] != '=')
		i++;
	lst_env->val = env_dup(var + i + 1, ft_strlen(var + i), gc);
	if (var[i - 1] == '+')
		i --;
	lst_env->var = env_dup(var, i + 1, gc);
	lst_env->next = NULL;
	return (lst_env);
}

t_env	*get_env(char **env, t_gc *gc)
{
	t_env	*lst_env;
	int		i;

	i = 0;
	if (*env == NULL)
		return (NULL);
	lst_env = get_envlst(env[i], gc);
	i++;
	while (env[i])
	{
		add_env(lst_env, get_envlst(env[i], gc));
		i++;
	}
	return (lst_env);
}
