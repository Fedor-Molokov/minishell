# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/24 22:57:41 by dmarsell          #+#    #+#              #
#    Updated: 2020/08/19 15:52:24 by dmarsell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Wextra -g

HD = minishell.h

OBJ_DIR = obj_minishell

LIBFT_DIR = libft

LIBFT = libft.a

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

SRC = main.c \
		builtin.c \
		echo.c \
		cd.c \
		env.c \
		setenv.c \
		launch.c \
		unsetenv.c \
		additional.c 

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)
	@echo "\033[32m [OK] \033[0m\033[32mCompiling execution file:\033[36m" $(NAME) 
	@echo "\033[0m"
		
$(OBJ): $(OBJ_DIR)/%.o: ./%.c $(HD)
	@$(CC) -I $(HD) -o $@ -c $<
	@echo "\033[32m [OK] \033[0m\033[32mCompiling:\033[36m " $@

$(OBJ_DIR): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)
		@mkdir $(OBJ_DIR)
		@echo "\033[32m [OK] \033[0m\033[32mMaking catalog:\033[36m " $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[31m [OK] \033[0m\033[31mDeleting catalog and binaries:\033[33m " $(OBJ_DIR)
		@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m [OK] \033[0m\033[31mDeleting execution file:\033[33m " $(NAME)
		@make filecl -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
