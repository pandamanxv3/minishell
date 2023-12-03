
SRCS=	sources/ft_atoi.c\
		sources/ft_ch.c\
		sources/ft_dispatch.c\
		sources/ft_initabforlis.c\
		sources/ft_lessthan5.c\
		sources/ft_lst2init.c\
		sources/ft_morethan5.c\
		sources/ft_nodefirstremove.c\
		sources/ft_primesort.c\
		sources/ft_reverserotate.c\
		sources/ft_sort3.c\
		sources/ft_sortingch.c\
		sources/ft_swap.c\
		sources/ft_bestmoove.c\
		sources/ft_check.c\
		sources/ft_dispatchsorting.c\
		sources/ft_intochained.c\
		sources/ft_lis.c\
		sources/ft_mix1.c\
		sources/ft_nodeadd_back.c\
		sources/ft_nodelast.c\
		sources/ft_push_a.c\
		sources/ft_rotate.c\
		sources/ft_sort4.c\
		sources/ft_sortingmix1.c\
		sources/ft_testnum.c\
		sources/ft_bubblesort.c\
		sources/ft_checkdouble.c\
		sources/ft_dispatchsplit.c\
		sources/ft_isthisfromalis.c\
		sources/ft_lististing.c\
		sources/ft_mix2.c\
		sources/ft_nodeadd_front.c\
		sources/ft_nodelastremove.c\
		sources/ft_push_b.c\
		sources/ft_rr.c\
		sources/ft_sort5.c\
		sources/ft_sortingmix2.c\
		sources/main.c\
		sources/ft_cb.c\
		sources/ft_convert.c\
		sources/ft_exit.c\
		sources/ft_lengthstacks.c\
		sources/ft_lowerprice.c\
		sources/ft_mooveandwrite.c\
		sources/ft_nodeclear.c\
		sources/ft_nodenew.c\
		sources/ft_redeterminingprice.c\
		sources/ft_rrr.c\
		sources/ft_sortingcb.c\
		sources/ft_splitfree.c

SRCS_BONUS=	sources_bonus/ft_atoi.c\
			sources_bonus/ft_checkdouble.c\
			sources_bonus/ft_dispatchsplit.c\
			sources_bonus/ft_lst2init.c\
			sources_bonus/ft_nodeclear.c\
			sources_bonus/ft_nodelastremove.c\
			sources_bonus/ft_push_b.c\
			sources_bonus/ft_rr.c\
			sources_bonus/ft_strncmp.c\
			sources_bonus/get_next_line.c\
			sources_bonus/ft_bubblesort.c\
			sources_bonus/ft_convert.c\
			sources_bonus/ft_exit.c\
			sources_bonus/ft_nodeadd_back.c\
			sources_bonus/ft_nodefirstremove.c\
			sources_bonus/ft_nodenew.c\
			sources_bonus/ft_reverserotate.c\
			sources_bonus/ft_rrr.c\
			sources_bonus/ft_swap.c\
			sources_bonus/get_next_line_utils.c\
			sources_bonus/ft_check.c\
			sources_bonus/ft_dispatch.c\
			sources_bonus/ft_intochained.c\
			sources_bonus/ft_nodeadd_front.c\
			sources_bonus/ft_nodelast.c\
			sources_bonus/ft_push_a.c\
			sources_bonus/ft_rotate.c\
			sources_bonus/ft_splitfree.c\
			sources_bonus/ft_testnum.c\
			sources_bonus/main.c

# INCL=	include/ft_pushswap.h

NAME=	push_swap

NAME_BONUS= checker

CFLAGS= -Werror -Wall -Wextra -g

CC=	gcc

OBJS=	$(SRCS:.c=.o)

OBJS_BONUS=	$(SRCS_BONUS:.c=.o)

RM=	rm -f

all:	$(NAME)

bonus:	$(NAME_BONUS)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS):	$(OBJS_BONUS)
				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
clean:
		$(RM) $(OBJS) $(OBJS_BONUS)
fclean:	clean
		$(RM) $(OBJS) $(NAME) $(NAME_BONUS)
		

re:	fclean all

.PHONY:	fclean clean re all