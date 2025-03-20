NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

RM = rm -rf

SRCS = src/pipex.c src/utils.c libft/libft.a
SRCS_BONUS = src_bonus/pipex_bonus.c src_bonus/utils_bonus.c libft/libft.a src_bonus/norm_bonus.c

$(NAME): libft/libft.a $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

$(NAME_BONUS): libft/libft.a $(SRCS_BONUS)
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME_BONUS)

libft/libft.a:
	make -C libft

all: $(NAME)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(NAME) $(NAME_BONUS)
	make clean -C libft

fclean: clean
	make fclean -C libft

re: fclean all
