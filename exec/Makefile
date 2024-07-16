# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 09:58:08 by arbenois         #+#    #+#              #
#    Updated: 2023/11/27 10:29:26 by arbenois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

# Source and objet directories
SRC_DIR = ./src
OBJ_DIR = ./obj
DEP_DIR = ./dep

# Source files
SRCS =	main.c 										\
		parsing/check_function/check_command.c		\
		parsing/parse_in_struct.c					\
		parsing/parse_quote.c						\
		parsing/check_function/check_quote.c		\
		parsing/parse_argv.c						\
		parsing/parse_env.c							\
		parsing/heredoc/parse_heredoc.c				\
		parsing/heredoc/remove_heredoc.c			\
		exec/built_in_calls.c						\
		exec/handle_signal.c						\
		exec/ls.c									\
		exec/built_ins/pwd.c						\
		exec/built_ins/cd.c							\
		exec/built_ins/echo.c						\
		exec/built_ins/env.c						\
		exec/built_ins/unset.c						\
		exec/built_ins/export.c						\
		exec/built_ins/exit.c						\
		exec/execution/init_exec.c					\
		exec/execution/here_doc_tester.c			\
		exec/execution/executor.c					\
		free/free.c									\
		utils/copy.c								\
		utils/ft_calloc.c							\
		utils/compare.c								\
		utils/linked_list.c							\
		utils/linked_follow.c						\
		utils/ft_split.c

# Objet files
OBJS =	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(DEP_DIR)/, $(SRCS:.c=.d))

# Executable Name
NAME = minishell

# Target
.SILENT: all clean fclean re

all: $(NAME)
	@echo "$(GREEN)Compilation completed successfully!$(NC)"

-include $(DEPS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Linking completed!$(NC)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(OBJ_DIR)/parsing $(DEP_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/parsing/heredoc $(DEP_DIR)/parsing/heredoc
	@mkdir -p $(OBJ_DIR)/parsing/check_function $(DEP_DIR)/parsing/check_function
	@mkdir -p $(OBJ_DIR)/exec $(DEP_DIR)/exec
	@mkdir -p $(OBJ_DIR)/exec/built_ins $(DEP_DIR)/exec/built_ins
	@mkdir -p $(OBJ_DIR)/exec/execution $(DEP_DIR)/exec/execution
	@mkdir -p $(OBJ_DIR)/free $(DEP_DIR)/free
	@mkdir -p $(OBJ_DIR)/utils $(DEP_DIR)/utils
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@
	@echo "$(GREEN)Compilation of $< completed!$(NC)"

clean:
	rm -fr $(OBJ_DIR) $(DEP_DIR)
	@echo "$(RED)Cleanup completed!$(NC)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)Deletion of the executable completed!$(NC)"

re: fclean all

.PHONY: all clean fclean re
