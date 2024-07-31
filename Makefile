CC       = GCC
NAME = cub3D
CFLAGS   = -Wall -Wextra -Werror -Imlx -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3 -g -fsanitize=address
#FLAGS = -Wall -Wextra -Werror -Imlx -g3 -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

SRCS     = src/main_cub3d.c			\
			src/handle_event.c		\
			src/mini_maps.c 		\
			src/parse_maps.c 		\
			src/check_maps.c 		\
			src/check_arg.c 		\
			src/check_arg2.c 		\
			src/raycasting.c 		\
			src/raycasting_utils.c 	\
			src/mlx_img.c 			\
			src/utils.c 			\
			src/movements.c 		\
			src/interaction.c
OBJ      = $(SRCS:.c=.o)
OBJDIR = obj/

BON_SRCS = bonus/src/main_cub3d_bonus.c		\
			bonus/src/handle_event.c		\
			bonus/src/handle_event2.c		\
			bonus/src/mini_maps.c 			\
			bonus/src/parse_maps.c 			\
			bonus/src/check_maps.c 			\
			bonus/src/check_arg.c 			\
			bonus/src/check_arg2.c 			\
			bonus/src/raycasting.c 			\
			bonus/src/raycasting_mirror.c 	\
			bonus/src/raycasting_utils.c 	\
			bonus/src/mlx_img.c 			\
			bonus/src/utils.c 				\
			bonus/src/doors.c 				\
			bonus/src/life.c 				\
			bonus/src/movements.c 			\
			bonus/src/parse_weapon.c 		\
			bonus/src/draw_weapon.c 		\
			bonus/src/interaction.c

BON_OBJ  = $(BON_SRCS:.c=.o)

LIB      = $(LIBFT)libftprintf.a
LIBFT    = ./inc/Printf/

MINI = ./inc/minilibx/
LIBX = $(MINI)libmlx.a

INC_BONUS = -I ./bonus/inc -I ./inc -I ./inc/minilibx

.PHONY: all clean fclean re bonus

all: $(NAME)
	

$(NAME): $(OBJ) libftprintf.a $(LIBX)
	@$(CC) $(CFLAGS) $^ -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Cube3d made"

bonus: $(BON_OBJ) libftprintf.a $(LIBX)
	@$(CC) $(CFLAGS) $(INC_BONUS) $^ -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Cube3d bonus made"

%.o : %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

add:
	git add bonus/ src/ inc/ maps/ texture/ weapon_sprites/ Makefile .gitignore

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
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)
	@echo "fclean done"
	
fclean_mlx:
	@make -C $(MINI) clean

re: fclean all
	@echo "make re done"

