# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdebs <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/25 21:05:50 by wdebs             #+#    #+#              #
#    Updated: 2017/04/28 22:43:38 by wdebs            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
IFLAGS = -I includes

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c \
	  ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c \
	  ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c \
	  ft_strstr.c ft_tolower.c ft_toupper.c ft_memalloc.c ft_memdel.c \
	  ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	  ft_strjoin.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
	  ft_strtrim.c ft_strsplit.c ft_putchar.c ft_putstr.c ft_putendl.c \
	  ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_itoa.c ft_lstnew.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
	  ft_lstmap.c ft_swap.c ft_isupper.c ft_islower.c ft_isblank.c ft_strcspn.c \
	  ft_strtrim.c grab_line.c ft_setenv.c ft_unsetenv.c b_tree.c \
	  ft_getchar_mod.c ft_insrtchar.c ft_delchar.c ft_strspn.c ft_tdnew.c \
	  ft_reallloc2.c ft_twodlen.c ft_twodfree.c ft_strlcmp.c \
	  get_next_line.c \

OBJ = ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
	  ft_isdigit.o ft_isprint.o ft_memccpy.o ft_memchr.o ft_memcmp.o \
	  ft_memcpy.o ft_memmove.o ft_memset.o ft_strcat.o ft_strchr.o \
	  ft_strcmp.o ft_strcpy.o ft_strdup.o ft_strlcat.o ft_strlen.o \
	  ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnstr.o ft_strrchr.o \
	  ft_strstr.o ft_tolower.o ft_toupper.o ft_memalloc.o ft_memdel.o \
	  ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o \
	  ft_strjoin.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o \
	  ft_strtrim.o ft_strsplit.o ft_putchar.o ft_putstr.o ft_putendl.o \
	  ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
	  ft_itoa.o ft_lstnew.o ft_lstadd.o ft_lstdel.o ft_lstdelone.o ft_lstiter.o \
	  ft_lstmap.o ft_swap.o ft_isupper.o ft_islower.o ft_isblank.o ft_strcspn.o \
	  ft_strtrim.o grab_line.o ft_setenv.o ft_unsetenv.o b_tree.o \
	  ft_getchar_mod.o ft_insrtchar.o ft_delchar.o ft_strspn.o ft_tdnew.o \
	  ft_realloc2.o ft_twodlen.o ft_twodfree.o ft_strlcmp.o \
	  get_next_line.o \

CFLAGS = -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME):
	$(CC) $(IFLAGS) $(CFLAGS) *.c
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
