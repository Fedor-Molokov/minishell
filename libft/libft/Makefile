# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/20 20:42:18 by dmarsell          #+#    #+#              #
#    Updated: 2020/06/16 21:35:15 by dmarsell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c	ft_memccpy.c	ft_putendl.c	ft_strcmp.c	ft_strlen.c	ft_strrchr.c\
ft_bzero.c	ft_memchr.c	ft_putendl_fd.c	ft_strcpy.c	ft_strmap.c	ft_strsplit.c\
ft_isalnum.c	ft_memcmp.c	ft_putnbr.c	ft_strdel.c	ft_strmapi.c	ft_strstr.c\
ft_isalpha.c	ft_memcpy.c	ft_putnbr_fd.c	ft_strdup.c	ft_strncat.c	ft_strsub.c\
ft_isascii.c	ft_memdel.c	ft_putstr.c	ft_strequ.c	ft_strncmp.c	ft_strtrim.c\
ft_isdigit.c	ft_memmove.c	ft_putstr_fd.c	ft_striter.c	ft_strncpy.c	ft_tolower.c\
ft_isprint.c	ft_memset.c	ft_strcat.c	ft_striteri.c	ft_strnequ.c	ft_toupper.c\
ft_itoa.c	ft_putchar.c	ft_strchr.c	ft_strnew.c ft_strjoin.c \
ft_memalloc.c	ft_putchar_fd.c	ft_strclr.c	ft_strlcat.c	ft_strnstr.c

OBJS = $(SRC:.c=.o)

HD = libft.h

all: $(NAME)
	
$(NAME):
	@gcc -Wall -Wextra -c $(SRC) -I $(HD)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)
		@echo "\033[32m [OK] \033[0m\033[32mLinking library binary:\033[36m " $(NAME)

clean: 
		@/bin/rm -f $(OBJS)
		
fclean: clean
		@/bin/rm -f $(NAME)
		@echo "\033[31m [OK] \033[0m\033[31mDeleting library binary:\033[33m " $(NAME)
re: fclean all
