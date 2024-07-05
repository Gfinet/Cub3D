CC       = GCC
NAME = cub3D
CFLAGS   = -Wall -Wextra -Werror -fsanitize=address -Imlx -g3 -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3
#FLAGS = -Wall -Wextra -Werror -Imlx -g3 -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

SRCS     = src/main_cub3d.c		\
			src/handle_event.c	\
			src/mini_maps.c 	\
			src/parse_maps.c 	\
			src/check_maps.c 	\
			src/check_arg.c 	\
			src/check_arg2.c 	\
			src/raycasting.c 	\
			src/mlx_img.c 		\
			src/utils.c 		\
			src/background.c 	
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

add:
	git add src/ inc/ maps/ texture/ Makefile .gitignore

$(LIBX):
	@make -C $(MINI)
	@echo "library mlx made"

libftprintf.a:
	@make -C $(LIBFT)
	@cp $(LIB) .
	@mv $(LIB) $(NAME)


clean:
	@rm -rf $(OBJ)
	@rm -rf $(BON_OBJ)
#@make -C $(MINI) clean
	@make -C $(LIBFT) clean
	@echo "clean done"

fclean: clean
	@rm -rf libftprintf.a
#@make -C $(MINI) clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)
	@echo "fclean done"
	

bonus : $(BON_OBJ) libftprintf.a libmlx.a
	@$(CC) $(CFLAGS) $^ -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Cube3d bonus made"

re: fclean all
	@echo "make re done"

