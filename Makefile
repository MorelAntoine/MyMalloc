##
## Makefile for Makefile in Documents/epitech/annee_2/semestre_2/unix_memory/PSU_2016_malloc/dev
##
## Made by Antoine MOREL
## Login   <morel_j@epitech.net>
##
## Started on  Thu Jan 26 00:02:22 2017 Antoine MOREL
## Last update Thu Jan 26 00:02:22 2017 Antoine MOREL
##

NAME		=	libmy_malloc.so

SRCS		=	memory.c	\
			malloc.c	\
			realloc.c	\
			free.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-fPIC -Wextra -Wall

CC		=	gcc

RM		=	rm -rf

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(OBJS) -shared -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
