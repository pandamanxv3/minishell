/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:31:52 by cbarbit           #+#    #+#             */
/*   Updated: 2022/05/30 14:44:00 by cbarbit          ###   ########.fr       */
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

// void	add_env(t_env *env, t_env **to_add)
// {
// 	t_env	*temp;

// 	temp = env;
// 	//printf("ADRESSE 2: %p\n", to_add);
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = *to_add;
// }

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
	lst_env->var = env_dup(var, i + 1, gc);
	lst_env->val = env_dup(var + i + 1, ft_strlen(var + i), gc);
	//printf("lst_env->val = %s\n", lst_env->val);
	lst_env->next = NULL;
	return (lst_env);
}

// t_env	**get_envlst(char *var, t_gc *gc)
// {
// 	t_env	*lst_env;
// 	t_env	**pt_env;
// 	int		i;

// 	i = 0;
// 	lst_env = ft_malloc("env", 0, "erreur malloc lst_env", gc);
// 	pt_env = &lst_env;
// 	while (var[i] != '=')
// 		i++;
// 	lst_env->var = env_dup(var, i + 1, gc);
// 	lst_env->val = env_dup(var + i + 1, ft_strlen(var + i), gc);
// 	//printf("lst_env->val = %s\n", lst_env->val);
// 	lst_env->next = NULL;
// 	//printf("ADRESSE 1: %p\n", lst_env);
// 	return (pt_env);
// }

t_env	*get_env(char **env, t_gc *gc)
{
	t_env	*lst_env;
	int		i;

	i = 0;
	lst_env = get_envlst(env[i], gc);
	i++;
	while (env[i])
	{
		add_env(lst_env, get_envlst(env[i], gc));
		i++;
	}
	return (lst_env);
}

// t_env	**get_env(char **env, t_gc *gc)
// {
// 	t_env	**lst_env;
// 	t_env	*pt_env;
// 	int		i;

// 	i = 0;
// 	lst_env = get_envlst(env[i], gc);
// 	pt_env = *lst_env;
// 	i++;
// 	while (env[i])
// 	{
// 		add_env(pt_env, get_envlst(env[i], gc));
// 		i++;
// 	}
// 	return (lst_env);
// }


// void	print_env(t_env *env)
// {
// 	t_env	*temp;

// 	temp = env;
// 	while (temp)
// 	{
// 		printf("%s", temp->var);
// 		printf("=");
// 		printf("%s\n", temp->val);
// 		if (!temp->next)
// 			break ;
// 		temp = temp->next;
// 	}
// }
