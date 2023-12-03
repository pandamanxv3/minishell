/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudjel <aboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:37:43 by aboudjel          #+#    #+#             */
/*   Updated: 2022/02/21 00:46:20 by aboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSHSWAP_H
# define FT_PUSHSWAP_H
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct t_node
{
	int				price;
	int				number;
	int				sempaipos;
	int				typeofmoove;
	int				pos;
	long int		nb;
	struct t_node	*next;
	struct t_node	*previous;
}t_node;

typedef struct t_struct
{
	int		*tab;
	int		*actualtab;
	int		*lis;
	int		length;
	int		lislength;
	int		lengtha;
	int		lengthb;
	int		argv;
	t_node	*lst;
	t_node	*lst2;
}t_struct;

t_node	*ft_nodelast(t_node *lst);
t_node	*ft_nodenew(int number, t_struct *list);
t_node	*ft_lst2init(void);
t_node	*ft_intochained(int *tab, int argc, int i, t_struct *list);

void	ft_redeterminingprice(t_struct *list);
void	ft_nodeclear(t_struct **list);
void	ft_nodefirstremove(t_node **lst);
void	ft_nodelastremove(t_node **lst);
void	ft_nodeadd_front(t_node **lst, t_node *new);
void	ft_nodeadd_back(t_node **lst, t_node *new);
void	ft_exit(t_struct **list, char **argv);
void	ft_exitbis(t_struct *list);
void	ft_exitbis2(t_struct *list);
void	ft_exitbis3(t_struct *list);
void	ft_exitbis4(t_struct *list, int *lis);
void	ft_convert(char **argv, t_struct *src, int j);
void	ft_push_a(t_node **lst, t_node **lst2, t_struct *list);
void	ft_push_b(t_node **lst, t_node **lst2, t_struct *list);
void	ft_swap(t_node *lst);
void	ft_rotate(t_node **lst, t_struct *list);
void	ft_reverserotate(t_node **lst, t_struct *list);
void	ft_rr(t_node **lst, t_node **lst2, t_struct *list);
void	ft_rrr(t_node **lst, t_node **lst2, t_struct *list);
void	ft_mooveandwrite(t_struct *list, int index);
void	ft_sort3(t_struct *list);
void	ft_sort4(t_struct *list);
void	ft_sort5(t_struct *list);
void	ft_lessthan5(t_struct *list);
void	ft_lististing(int *lis, t_struct *list);
void	ft_initabforlis(t_struct *list);
void	ft_lis(t_struct	*list, int i, int j);
void	ft_primesort(t_struct *list);
void	ft_sortingch(t_struct *list, t_node *best, int sempaiA);
void	ft_sortingcb(t_struct *list, t_node *best, int sempaiA);
void	ft_sortingmix1(t_struct *list, t_node *best, int sempaiA);
void	ft_sortingmix2(t_struct *list, t_node *best, int sempaiA);
void	ft_lengthstacks(t_struct	*list);
void	ft_dispatchsorting(t_struct	*list, int lowestprice);
void	ft_morethan5(t_struct	*list);
void	ft_bubblesort(int *src, int argc);
void	ft_check(t_struct *list, int i);
void	ft_dispatch(t_struct *list);

int		ft_bestmoove(int ch, int cb, int mix1, int mix2);
int		ft_lowerprice(int ch, int cb, int mix1, int mix2);
int		main(int argc, char **argv);
int		ft_ch(t_struct *list, int a, int posb, long int nbmin);
int		ft_cb(t_struct *list, int a, int posb, long int nbmin);
int		ft_mix1(t_struct *list, int a, int posb, long int nbmin);
int		ft_mix2(t_struct *list, int a, int posb, long int nbmin);
int		ft_isthisfromalis(int a, t_struct	*list);
int		ft_atoi(const char *str, t_struct *src, char **argv);
int		ft_testnum(char *str);
int		ft_checkdouble(int *tab, int argc);

char	**ft_splitfree(char **tab);
char	**ft_dispatchsplit(char	*s, t_struct *list);

#endif