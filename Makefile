NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes
LDFLAGS		= -lreadline -lhistory
LIBFT_DIR	= libft_git
OBJ_DIR		= obj
VPATH		= main:parsing:srcs:srcs/built_ins:srcs/command_manager:srcs/utils
LIBFT		= $(LIBFT_DIR)/libft.a
SRCS		= main.c \
			  lexer.c \
			  lexer2.c \
			  parser.c \
			  expander.c \
			  expander2.c \
			  expander3.c \
			  expander4.c \
			  expander5.c \
			  command_manager.c \
			  command_manager2.c \
			  command_manager3.c \
			  command_manager4.c \
			  handle_signals.c \
			  utils.c \
			  utils2.c \
			  utils3.c \
			  utils4.c \
			  utils5.c \
			  utils6.c \
			  utils7.c \
			  utils8.c \
			  utils9.c \
			  utils10.c \
			  utils11.c \
			  utils12.c \
			  utils13.c \
			  utils14.c \
			  echo.c \
			  pwd.c \
			  cd.c \
			  exit.c \
			  env.c \
			  export.c \
			  unset.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) | $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@make -sC $(LIBFT_DIR) all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) all fclean

re: fclean all

.PHONY: all clean fclean re
