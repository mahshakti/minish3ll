# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/11/06 11:39:30 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES_C		= ft_atoi.c ft_isprint.c ft_isspace.c ft_itoa.c ft_split.c \
			ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_substr.c ft_strcmp.c \
			ft_strchr.c ft_strconcat.c ft_fdprint.c ft_calloc.c ft_strltrim.c

NAME		= libft.a
SRCS_DIR	= .
OBJS_DIR	= ../obj
O_FILES		= $(addprefix $(OBJS_DIR)/,$(FILES_C:%.c=%.o))

AR			= ar -crs
CC			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g -O0 -I.
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all:			$(NAME)

$(NAME):		$(O_FILES) | $(OBJS_DIR)
	@echo "$< > $@"
	@$(AR) $(NAME) $(O_FILES)

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
