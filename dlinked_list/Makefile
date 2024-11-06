# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/11/06 11:39:37 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES_C 	= dlist_add_before.c dlist_clear.c dlist_remove.c dlist_has.c	\
			dlist_last.c dlist_size.c dlist_add_after.c dlist_remove_before.c	\
			dlist_new.c dlist_free.c

NAME		= dlinked_list.a
SRCS_DIR	= .
OBJS_DIR	= ../obj
FILES_O		= $(addprefix $(OBJS_DIR)/,$(FILES_C:%.c=%.o))

AR			= ar -crs
CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g -O0 -I.
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:			$(NAME)

$(NAME):		$(FILES_O) | $(OBJS_DIR)
	@echo "$< > $@"
	@$(AR) $(NAME) $(FILES_O)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@echo "$< > $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# --------------------------------------

clean:
	clear
	@rm -fr $(OBJS_DIR) *.o 2>/dev/null

fclean: clean
	@rm -rf $(NAME) 2>/dev/null

re:	fclean all

.PHONY: all, clean, fclean, re
