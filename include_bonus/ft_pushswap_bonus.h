/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:37:43 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/11 16:25:39 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSHSWAP_BONUS_H
# define FT_PUSHSWAP_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

typedef struct t_node
{
	int				number;
	int				pos;
	struct t_node	*next;
	struct t_node	*previous;
}t_node;

typedef struct t_struct
{
	int		*tab;
	int		*actualtab;
	int		length;
	t_node	*lst;
	t_node	*lst2;
}t_struct;

t_node	*ft_nodelast(t_node *lst);
t_node	*ft_nodenew(int number);
t_node	*ft_lst2init(void);
t_node	*ft_intochained(int *tab, int argc, int i);

void	ft_nodeclear(t_struct **list);
void	ft_nodefirstremove(t_node **lst);
void	ft_nodelastremove(t_node **lst);
void	ft_nodeadd_front(t_node **lst, t_node *new);
void	ft_nodeadd_back(t_node **lst, t_node *new);
void	ft_exit(t_struct **list, char **argv);
void	ft_convert(char **argv, t_struct *src, int j);
void	ft_push_a(t_node **lst, t_node **lst2);
void	ft_push_b(t_node **lst, t_node **lst2);
void	ft_swap(t_node *lst);
void	ft_rotate(t_node **lst);
void	ft_reverserotate(t_node **lst);
void	ft_rr(t_node **lst, t_node **lst2);
void	ft_rrr(t_node **lst, t_node **lst2);
void	ft_dispatchchecker(t_struct *list, char *s);

void	ft_bubblesort(int *src, int argc);
void	ft_check(t_struct *list);
void	ft_dispatch(t_struct *list);

int		ft_strncmp(const char *stra, const char *strb, size_t length);
int		newline(char *str);
int		ft_strlen(const char *str);
int		main(int argc, char **argv);
int		ft_atoi(const char *str, t_struct *src, char **argv);
int		ft_testnum(char *str);
int		ft_checkdouble(int *tab, int argc);

char	*setupline(char *str, int fd);
char	*get_next_line(int fd);
char	*new_str(char *str);
char	*ft_substr(char const *str);
char	*ft_strstrjoin(char *s1, char *s2, int j, int i);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_splitfree(char **tab);
char	**ft_dispatchsplit(char	*s, t_struct *list);

#endif