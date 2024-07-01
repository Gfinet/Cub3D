CC       = GCC
NAME = cub3D
CFLAGS   = -Wall -Wextra -Werror #-g -fsanitize=address


SRCS     = src/main_cub3d.c \
			src/handle_event.c
OBJ      = $(SRCS:.c=.o)

# BON_SRCS = bonus/main_cub3d_bonus.c
# BON_OBJ  = $(BON_SRCS:.c=.o)

LIB      = $(LIBFT)libftprintf.a
LIBFT    = ./Printf/

LIBMLX   = ./MLX42
LIBS	 = MLX42/build/libmlx42.a -ldl -lglfw -pthread

HEADERS  = -I . -I $(LIBMLX)/include


.PHONY: all clean fclean re bonus

all: libmlx42.a $(NAME)
	

$(NAME): $(OBJ) libftprintf.a 
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) $^ -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)
	@echo "Cube3d made"

%.o : %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

libmlx42.a:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libftprintf.a:
	@make -C $(LIBFT)
	@cp $(LIB) .
	@mv $(LIB) $(NAME)


clean:
	@rm -rf $(OBJ)
	@rm -rf $(BON_OBJ)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean
	@echo "clean done"

fclean: clean
	@rm -rf libftprintf.a
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)
	@echo "fclean done"
	

bonus : $(BON_OBJ) libftprintf.a mlx/libmlx.a
	@$(CC) $(CFLAGS) $^ -framework OpenGL -framework AppKit -o $(NAME)
	@echo "fractol bonus made"

re: fclean all
	@echo "make re done"

