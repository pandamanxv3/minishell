/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:00:14 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 19:03:43 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *str)
{
	char	*dst;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && (str[i] != '\n'))
		i++;
	dst = malloc(sizeof(char) * i + 2);
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dst[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strstrjoin(char *s1, char *s2, int j, int i)
{
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!dst)
		return (NULL);
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	free(s1);
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[i] = '\0';
	}
	if (!s2 || !s1)
		return (NULL);
	return (ft_strstrjoin(s1, s2, j, i));
}
