# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juasanto <juasanto@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/13 13:19:09 by juasanto          #+#    #+#              #
#    Updated: 2022/03/13 13:19:40 by juasanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo
LIBFT 		= 	libft.a
LIB_DIR		=	Libft/
OBJ_DIR		=	obj/
SRCS_DIR	=	sources/
SRCS		=	philo.c \
				p_init.c \
				p_chk_args.c \
				p_utils.c \
				p_status.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

NOW			=	$(shell date +"%d-%m-%y %H:%M")

LFLAGS = -I includes/
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
DEBUGGING = -ggdb
OPTIMIZING = -O3
CC = clang
LINUX-CC = cc
RM = rm -rf
AR = ar rc
RANLIB = ranlib
NORM = /usr/bin/norminette

RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
CYAN = \033[36m



all: $(NAME)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
		@echo Create: $(NAME) Object directory
		@mkdir -p $(OBJ_DIR)
#		$(CC) -c $(CFLAGS) $(DEBUGGING) $(LFLAGS) $< -o $@
		$(CC) -c $(CFLAGS) $(DEBUGGING) $(LFLAGS) $< -o $@ -pthread

$(NAME): $(OBJS)
#		@echo "$(CYAN)=========== Compilando LIBFT.A ==========="
#		make -C $(LIB_DIR)
#		@echo "=========== DONE ==========$(RESET)"

		@echo "$(YELLOW)=========== Compilando $(NAME) ==========="
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) -pthread
#		$(CC)$(CFLAGS) $(OBJS) $(LFLAGS) $(LIB_DIR)$(LIBFT) -o $(NAME)
		@echo "=========== DONE ==========$(RESET)"
clean:
		@echo "$(PINK)========== CLEAN =========="
		$(RM) $(OBJ_DIR)
		$(RM) $(OBJS)
#		make -C $(LIB_DIR) clean
		@echo "$(PINK)=========== DONE ===========$(RESET)"
fclean: clean
		@echo "$(RED)========== FCLEAN =========="
		$(RM) $(NAME)
#		make -C $(LIB_DIR) fclean
		@echo "$(RED)=========== DONE ===========$(RESET)"
git_push: fclean
		@echo "$(RED)========== GIT_PUSH =========="
		git add *
		git commit -m "Philosofers - $(NOW)"
		git push 
		git status
@echo "$(RED)=========== DONE ===========$(RESET)"
bonus: all
re: fclean all
norm: all
		$(NORM) $(SRC);

