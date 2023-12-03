/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:00:19 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 18:19:21 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_pushswap_bonus.h"

int	newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-2);
}

char	*new_str(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (newline(str) < 0)
	{
		free(str);
		return (NULL);
	}
	while (str[i] && str[i] != '\n')
		i++;
	tmp = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (str[i + j])
	{
		tmp[j] = str[i + j];
		j++;
	}
	tmp[j] = '\0';
	free (str);
	return (tmp);
}

char	*setupline(char *str, int fd)
{
	int		nread;
	char	*buffer;

	nread = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (nread && (newline(str) < 0))
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[nread] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = setupline(str, fd);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	tmp = ft_substr(str);
	str = new_str(str);
	return (tmp);
}
