# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eric <eric@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/16 13:20:00 by eric             #+#    #+#              #
#    Updated: 2026/04/16 13:20:00 by eric            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# VARIABLES
# ==============================================================================

# Compiler and flags
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror -g3
INCLUDES		:= -I./inc -I./libft

# Directories
LIBFT_DIR		:= libft
MANDATORY_DIR	:= mandatory
BONUS_DIR		:= bonus
OBJ_DIR			:= obj

# Output
NAME			:= ft_malcolm
LIBFT_A			:= $(LIBFT_DIR)/libft.a

# Source files
LIBFT_SRCS		:=  $(LIBFT_DIR)/ft_atoi.c \
					$(LIBFT_DIR)/ft_strcmp.c \
					$(LIBFT_DIR)/ft_strdup.c \
					$(LIBFT_DIR)/ft_strlen.c \
					$(LIBFT_DIR)/ft_memset.c \
					$(LIBFT_DIR)/ft_memcmp.c \
					$(LIBFT_DIR)/ft_memcpy.c

MANDATORY_SRCS	:= $(MANDATORY_DIR)/main.c \
				   $(MANDATORY_DIR)/parsing.c \
				   $(MANDATORY_DIR)/socket.c \
				   $(MANDATORY_DIR)/sniffer.c \
				   $(MANDATORY_DIR)/signal.c \
				   $(MANDATORY_DIR)/utils.c

ALL_SRCS		:= $(LIBFT_SRCS) $(MANDATORY_SRCS)

# Object files
LIBFT_OBJS		:= $(LIBFT_SRCS:%.c=$(OBJ_DIR)/%.o)
MANDATORY_OBJS	:= $(MANDATORY_SRCS:%.c=$(OBJ_DIR)/%.o)
ALL_OBJS		:= $(LIBFT_OBJS) $(MANDATORY_OBJS)

# ==============================================================================
# COLORS
# ==============================================================================

RED				:= \033[0;31m
GREEN			:= \033[0;32m
YELLOW			:= \033[0;33m
BLUE			:= \033[0;34m
RESET			:= \033[0m

# ==============================================================================
# RULES
# ==============================================================================

.PHONY: all clean fclean re up down

all: $(NAME)

$(NAME): $(ALL_OBJS) $(LIBFT_A)
	@echo "$(BLUE)Linking $@...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLU DES) -o $@ $(MANDATORY_OBJS) $(LIBFT_A) -lm
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(LIBFT_A): $(LIBFT_OBJS)
	@echo "$(BLUE)Creating libft.a...$(RESET)"
	@ar rcs $@ $^
	@echo "$(GREEN)✓ libft.a created!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing binaries...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(LIBFT_A)
	@echo "$(GREEN)✓ All binaries removed!$(RESET)"

re: fclean all

# ==============================================================================
# DOCKER
# ==============================================================================

up:
	@echo "$(BLUE)Starting Docker containers...$(RESET)"
	@cd malcolm_lab && sudo docker compose up --build
	@echo "$(GREEN)✓ Containers are running!$(RESET)"

down:
	@echo "$(RED)Stopping Docker containers...$(RESET)"
	@cd malcolm_lab && sudo docker compose down
	@echo "$(GREEN)✓ Containers stopped!$(RESET)"

# ==============================================================================
# INFO
# ==============================================================================

.PHONY: help
help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)     - Compile the entire project"
	@echo "  $(GREEN)clean$(RESET)   - Remove object files"
	@echo "  $(GREEN)fclean$(RESET)  - Remove object files and binaries"
	@echo "  $(GREEN)re$(RESET)      - Recompile everything"
	@echo "  $(GREEN)help$(RESET)    - Display this message"
