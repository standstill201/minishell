# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 15:07:43 by gychoi            #+#    #+#              #
#    Updated: 2023/02/09 16:10:55 by gychoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = executor

CC = cc
CFLAGS = -Wall -Wextra -Werror

LFTDIR = ../LIBFT/
BLDDIR = ./build/

LIBFT = $(LFTDIR)libft.a
LFTLIB = -L$(LFTDIR) -lft

SRCS = executor.c \
	   test_input.c

OBJS = $(patsubst %.c, %.o, $(SRCS))
OBJECT = $(addprefix $(BLDDIR), $(OBJS))

$(NAME): $(OBJECT) | $(LIBFT)
	$(CC) $(CFLAGS) $(LFTLIB) $(OBJECT) -o $@

$(BLDDIR):
	@mkdir -p $(BLDDIR)

$(BLDDIR)%.o: %.c | $(BLDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LFTDIR)

all: $(NAME)

clean:
	make -C $(LFTDIR) clean
	rm -rf $(BLDDIR)

fclean: clean
	make -C $(LFTDIR) fclean
	rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
