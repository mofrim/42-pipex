# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 00:03:28 by fmaurer           #+#    #+#              #
#    Updated: 2024/10/02 00:17:56 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS_IN = ./pipex.c

SRCS = $(patsubst ./%.c,%.c,$(SRCS_IN))

OBJDIR = obj
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

CC = clang
CFLAGS = -Wall -Werror -Wextra

GRN = \033[1;32m
RED = \033[1;31m
WHT = \033[1;37m
EOC = \033[1;0m
YLW = \033[1;33m
MSGOPN = $(YLW)[[$(GRN)
MSGEND = $(YLW)]]$(EOC)

log_msg = $(MSGOPN) $(1) $(MSGEND)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

debug: $(SRCS)
	$(CC) -g $(CFLAGS) -o pipex $^

$(OBJDIR):
	mkdir -p obj

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean debug
