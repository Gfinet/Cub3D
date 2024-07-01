/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djksafjhdsfj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:39:24 by lvodak            #+#    #+#             */
/*   Updated: 2024/06/12 19:29:54 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "lib/libft/headers/libft.h"
# include "lib/libft/headers/get_next_line_bonus.h"
# include "lib/libft/headers/ft_printf.h"
# include "lib/MLX42/include/MLX42/MLX42.h"

# define WIDTH 2400
# define LENGTH 1400
# define ERR_IMG "Error\nImage not loaded!"
# define ERR_XPM "Error\nXPM not loaded!"
# define ERR_NOCOLL "Error\nNot Enough Collectibles\n"

typedef struct s_maplst
{
	char			*line;
	struct s_maplst	*prev;
	struct s_maplst	*next;
}	t_maplst;

typedef struct s_point
{
	int	x;
	int	y;
	int	rx;
	int	ry;
	int	z;
}	t_point;

typedef struct s_pacmon
{
	char			*name;
	mlx_image_t		*front;
	mlx_image_t		*back;
	mlx_image_t		*left;
	mlx_image_t		*right;
	int				present;
}	t_pacmon;

typedef struct s_map_info
{
	int			length;
	int			width;
	int			exit;
	int			collectibles;
	int			tot_collectibles;
	t_pacmon	*player;
	int			possible;
	int			p_size;
	mlx_t		*mlx;
	mlx_image_t	***all_img;
	mlx_image_t	**coll_img;
	mlx_image_t	*exit_img;
}	t_map_info;

typedef struct s_collectibles
{
	xpm_t					*badges;
	int						unused;
	int						nbr;
	int						left;
	struct s_collectibles	*next;
}	t_collectibles;

typedef struct s_menu
{
	void		*mlx;
	mlx_image_t	*cursor;
	mlx_image_t	*all[6];
}	t_menu;

//parsing && parsing_utils
int				count_collect(t_maplst *map);
int				map_maker(t_maplst	*map, t_map_info *data);
t_maplst		*init_parsing(char *file, t_map_info *info);
int				check_map_value(t_maplst *map, t_map_info *info, int *start,
					t_maplst **start_line);
int				backtracking(t_maplst *map, t_map_info *info, int i);
//player_menu
int				player_construction(void);
void			take_starter_sprites(mlx_t *mlx, int player_info,
					t_pacmon *player);
void			refresh_player(t_pacmon	*player);
//mechanic
int				next_step_is_wall(t_map_info data, mlx_instance_t instance,
					int dir);
void			collect_collectible(t_map_info *data, mlx_instance_t instance);
void			end_game(t_map_info *data, mlx_instance_t instance);
//hook
void			hook_movements(void *param);
void			hook_menu(struct mlx_key_data keydata, void *param);
void			close_menu(void *param);
//movements
void			refresh_player(t_pacmon	*player);
void			move_up(t_pacmon *player, t_map_info *data);
void			move_down(t_pacmon *player, t_map_info *data);
void			move_right(t_pacmon *player, t_map_info *data);
void			move_left(t_pacmon *player, t_map_info *data);
//collectibles
void			choose_collectible(t_map_info *data, t_collectibles **collect,
					t_point point);
t_collectibles	*collectibles_struct(t_maplst *map);
//walls
int				check_surroundings(t_maplst *lines, t_point *point,
					t_map_info *data);
//map_maker
void			xpm_to_image(t_map_info *data, xpm_t *xpm, t_point point,
					int z);
int				map_maker(t_maplst *map, t_map_info *data);
//init_player
void			init_player(t_map_info *data, t_point point);
mlx_image_t		*load_player_image(mlx_t *mlx, char *sprite_path, char *part);
void			print_move(t_map_info *data, t_pacmon *pacmon);
void			free_game(t_map_info *data, t_point *last, int flag);
void			free_map(t_maplst **map);
void			free_coll_lst(t_collectibles **lst);

#endif