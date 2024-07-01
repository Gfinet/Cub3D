CC       = GCC
NAME = cub3D
CFLAGS   = -Wall -Wextra -Werror #-g -fsanitize=address


SRCS     = src/main_cub3d.c \
			src/handle_event.c
OBJ      = $(SRCS:.c=.o)

# BON_SRCS = bonus/main_cub3d_bonus.c
# BON_OBJ  = $(BON_SRCS:.c=.o)

LIB      = $(LIBFT)libftprintf.a
LIBFT    = ./inc/Printf/

MINI = ./inc/minilibx/
LIBX = $(MINI)libmlx.a




.PHONY: all clean fclean re bonus

all: $(NAME)
	

$(NAME): $(OBJ) libftprintf.a $(LIBX)
	@$(CC) $(CFLAGS) $^ -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Cube3d made"

%.o : %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(LIBX):
	@make -C $(MINI)
	@echo "library mlx made"

libftprintf.a:
	@make -C $(LIBFT)
	@cp $(LIB) .
	@mv $(LIB) $(NAME)
	@echo "library libftprintf made"


clean:
	@rm -rf $(OBJ)
	@rm -rf $(BON_OBJ)
	@make -C $(MINI) clean
	@make -C $(LIBFT) clean
	@echo "clean done"

fclean: clean
	@rm -rf libftprintf.a
	@make -C $(MINI) clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)
	@echo "fclean done"
	

bonus : $(BON_OBJ) libftprintf.a libmlx.a
	@$(CC) $(CFLAGS) $^ -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Cube3d bonus made"

re: fclean all
	@echo "make re done"

