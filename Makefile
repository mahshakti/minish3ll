# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesumore <jesumore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/11/25 16:50:01 by jesumore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN_C		= minishell.c
BUILTINS_C	= cd.c echo.c env.c exit.c export.c pwd.c unset.c builtin_utils.c
ENVIRON_C	= envp.c envp_utils.c
EXECUTOR_C	= executor.c executor_utils.c child.c child_utils.c fds.c fds_utils.c
INPUT_C		= expander.c lexer.c lexer_utils.c lexer_utils_2.c parser.c parser_utils.c
UTILS_C		= free.c utils.c signals.c dbg_print.c

LIBFT_A		= libft/libft.a
DL_LIST_A	= dlinked_list/dlinked_list.a

NAME		= minishell
VPATH		= . built_ins environment executor input utils
SRCS		= $(MAIN_C) $(BUILTINS_C) $(ENVIRON_C) $(EXECUTOR_C) $(INPUT_C) $(UTILS_C)
OBJS_DIR	= obj
OBJS		= $(addprefix $(OBJS_DIR)/,$(SRCS:%.c=%.o))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g -O0 -Wno-multichar -I.
OFLAGS		= $(CFLAGS)
CFLAGS		+= -lreadline -L. -l:$(LIBFT_A) -l:$(DL_LIST_A)
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) $(DL_LIST_A)
	@echo "$< > $@"
	@$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJS_DIR)/%.o:	%.c | $(OBJS_DIR)
	@echo "$< > $@"
	@$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT_A):
	@make -C "libft"

$(DL_LIST_A):
	@make -C "dlinked_list"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# --------------------------------------

clean:
	clear
	@rm -rf $(OBJS_DIR) **/*.o *.o 2>/dev/null

fclean: clean
	@rm -rf $(NAME) $(LIBFT_A) $(DL_LIST_A) 2>/dev/null

re:	fclean all

.PHONY: all, clean, fclean, re
