# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 13:47:21 by axcallet          #+#    #+#              #
#    Updated: 2023/06/16 17:31:51 by axcallet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


########## COLORS ##########

_END="\033[0m"
_RED="\033[0;31m"
_GREEN="\033[0;32m"
_YELLOW="\033[0;33m"
_CYAN="\033[0;36m"

########## ARGUMENTS ##########

NAME		= minishell
CXX			= clang
CXXFLAGS	= -Wall -Werror -Wextra -g

########## SOURCES ##########

SRC_DIR		= src
OBJ_DIR		= obj
BIN_DIR		= bin

MAKEFLAGS	+= --no-print-directory
SRC			= src/builtins/cd.c								\
			src/builtins/check_builtins.c					\
			src/builtins/echo.c								\
			src/builtins/env.c								\
			src/builtins/exit.c								\
			src/builtins/export.c							\
			src/builtins/print_tab.c						\
			src/builtins/pwd.c								\
			src/builtins/unset.c							\
			src/builtins/utils.c							\
			src/execution/exec_pipe.c						\
			src/execution/exec_pipe_utils.c					\
			src/heredoc/heredoc.c							\
			src/lst/data_tree/dtt_init.c					\
			src/lst/data_tree/dtt_refile.c					\
			src/lst/exec_lst_init.c							\
			src/lst/lst_free_utils.c						\
			src/parsing/input/check_syntax.c				\
			src/parsing/input/chevrons.c					\
			src/parsing/input/input.c						\
			src/parsing/input/input_2.c						\
			src/parsing/input/input_to_tab.c				\
			src/parsing/input/split.c						\
			src/parsing/refile/get_abs_path.c				\
			src/parsing/refile/refile_exec.c				\
			src/parsing/refile/refile_exec_utils.c			\
			src/parsing/utils/skip_argument.c				\
			src/parsing/variables/variables.c				\
			src/parsing/variables/variables_utils.c			\
			src/signals/signals.c							\
			src/signals/signals_2.c							\
			src/utils/free.c								\
			src/utils/get_everything_nbr/char_number.c		\
			src/utils/get_everything_nbr/chevron_number.c	\
			src/utils/get_everything_nbr/pipes_number.c		\
			src/utils/utils.c								\
			src/utils/utils_2.c								\
			src/main.c

HEADER		= inc/minishell.h

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT		= src/libft
INC			= -Iinc

########## RULES ##########

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo $(_GREEN)Compiling $(OBJ)...$(_END)
	@echo $(_GREEN)Compiling libft $(_END)
	@$(MAKE) bonus -C $(LIBFT)
	@$(CXX) $(CXXFLAGS) -L $(LIBFT) -o $(NAME) $(OBJ) -lreadline -l:libft.a

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(HEADER)
	@mkdir -p $(@D)
	@echo $(_CYAN)Compiling $<...$(_END)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	@echo $(_YELLOW)Cleaning $(OBJ)...$(_END)
	@rm -rf $(OBJ_DIR)
	@echo $(_YELLOW)Cleaning libft
	@$(MAKE) -s -C $(LIBFT) clean

fclean: clean
	@echo $(_RED)Cleaning $(NAME)...$(_END)
	@rm -rf $(NAME)
	@echo $(_RED)Cleaning libft.a
	@$(MAKE) -s -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
