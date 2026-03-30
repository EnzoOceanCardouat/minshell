NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCS = libft.h
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
	  ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	  ft_strjoin.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_strtrim.c ft_split.c ft_strlcat.c ft_itoa.c ft_splitutils.c
OBJ = $(SRC:.c=.o)
BNS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUS = $(BNS:.c=.o);
HEADERS=$(INCLUDES)ft.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADERS)

make bonus: $(OBJ) $(BONUS)
	@ar rcs $(NAME) $(OBJ) $(BONUS)

clean:
	@rm -f $(OBJ) $(BONUS)

fclean: clean
	@rm -f $(OBJ) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re

