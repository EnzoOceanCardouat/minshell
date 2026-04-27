NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I includes -I libft_git
LDFLAGS		= -lreadline -lhistory
LIBFT_DIR	= libft_git
OBJ_DIR		= obj
LIBFT		= $(LIBFT_DIR)/libft.a
SRCS		= main/main.c \
			  parsing/lexer.c \
			  parsing/parser.c \
			  parsing/expander.c \
			  srcs/command_manager.c \
			  srcs/handle_signals.c \
			  srcs/utils.c \
			  srcs/utils2.c \
			  srcs/utils3.c \
			  srcs/built_ins/echo.c \
			  srcs/built_ins/pwd.c \
			  srcs/built_ins/cd.c \
			  srcs/built_ins/exit.c \
			  srcs/built_ins/env.c \
			  srcs/built_ins/export.c \
			  srcs/built_ins/unset.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	@cd $(LIBFT_DIR) && make

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f *.o
	@cd $(LIBFT_DIR) && make clean

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBFT_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean re
