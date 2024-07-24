/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:41:55 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/24 23:09:14 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../inc/keycode.h"
# include "../../inc/Printf/ft_printf.h"
# include "../../inc/Printf/libft/libft.h"
# include "../../inc/minilibx/mlx.h"
# include <math.h>

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define MLX_SYNC_IMAGE_WRITABLE	1
# define MLX_SYNC_WIN_FLUSH_CMD		1
# define MLX_SYNC_WIN_CMD_COMPLETED	3

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 640 //1280
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1200 //2400
# endif

# define FRAME 4
# define JUMP_HEIGHT 80

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_data;

typedef struct s_mini_maps
{
	t_data	maps;
	int		witdh;
	int		height;
}	t_mini_maps;

typedef struct s_maps
{
	t_mini_maps	mini;
	char		**c_maps;
	char		**c_text;
	int			max_len;
	int			floor[3];
	int			ceil[3];
	int			m_height;
}	t_maps;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	prev_pos;
	int		run;
	int		move_v;
	int		move_h;
	int		turn;
}	t_player;

typedef struct s_door
{
	struct s_door	*next;
	t_point			coord;
	int				open;
	int				on_going;
}	t_door;

typedef struct s_cube
{
	void		*mlx;
	void		*win;
	t_maps		*lvl;
	t_data		*texture;
	t_data		door_texture[4];
	t_player	*player;
	t_data		*screen;
	t_door		*doors;
	int			frame;
	int			mouse;
}	t_cube;

typedef struct s_img
{
	void	*img;
	char	*path;
	int		witdh;
	int		height;
}	t_img;

typedef struct s_rcdata
{
	t_point			delta_dist;
	t_point			side_dist;
	t_point			side_dist_m;
	t_point			ray_dir;
	t_point			step;
	t_point			plane;
	t_point			dest;
	t_point			d_dest;
	t_point			p_dest;
	int				side;
	int				d_side;
	int				hit;
	double			camerx;
	double			perp_wall_dist;
	double			m_perp_wall_dist;
	double			d_perp_wall_dist;
	int				door;
}	t_rcdata;

typedef struct s_drawdata
{
	t_data			texture;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	int				line_height;
	int				pitch;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	double			step_f;
	int				mirr;
}	t_drawdata;

//handle_event.c
int		esc_handle(t_cube *cube);
int		fps(t_cube	*cube);
int		key_event(int keycode, t_cube *cube);
int		key_event_release(int keycode, t_cube *cube);
int		mouse_event(int x, int y, t_cube *cube);

//parse_maps.c
int		get_maps(t_cube *cube, char *file);
void	fill_maps(t_maps *lvl, char *str, int fd[2]);
void	set_floor_ceiling(int fl_ce[3], char *str);
void	set_map(t_maps *lvl, char *str, int fd[2]);

//check_maps.c
int		check_map(t_cube *cube);
int		check_elem(char *file);

//doors
t_data	data_img(char *file, t_cube *c);
void	load_door_texture(t_cube *cube);
t_door	*init_new_door(int x, int y);
void	get_all_doors(char **map, t_cube *c);
t_door	*find_door(t_cube *c, float x, float y);

//check_arg
int		check_arg(t_cube *cube, char *file);
int		check_elem(char *file);
int		check_line(char *str);
char	*get_text_dir(char *str);
int		get_dir(char *str);

//interations
void	find_and_open_door(t_door *door, t_player *player);
int		is_not_wallz(t_cube *c, t_point new_p, t_player *player);

//mini_maps
void	draw_mini_background(t_maps *lvl);
int		*get_ind(int i[2], int w_h[2], t_maps *lvl);
void	draw_maps(t_cube *cube);
int		make_mini(t_cube *cube, t_maps *lvl);

//mlx_img
void	get_player_pos(t_cube *cube);
void	fill_map_char(t_maps *lvl, char c);
void	draw_mini_pixel(t_maps *lvl, int w_h[2], int i[2]);
void	draw_player(t_cube *cube);
void	draw_doom(t_cube *cube);

//movements
void	update_player(t_cube *cube, t_player *player);
void	turn(t_cube *cube, double angle, int frame);

//raycast
void	calculate_perp_wall_dist(t_rcdata *data, int mirr);
double	fix_texture_pos(t_rcdata dt, t_player pl);
void	rcdda(t_cube *cube, char **map, t_player player);

void	draw_mirr_frame(t_data *screen, t_drawdata dt, int x, t_rcdata data);
void	get_door_draw_data(t_drawdata *dt, t_rcdata data, t_cube *c);
void	draw_door(t_data *screen, int x, t_rcdata data, t_cube *c);
void	update_mirror(t_rcdata *data, char **map);

void	pick_texture(t_drawdata *dr, t_rcdata dt, t_cube *cube, int door_text);
void	set_dda_ray_delta(t_rcdata *data, t_player player, int x);
void	set_side_dist_and_step(t_player p, t_rcdata *dt);
void	check_hit_target(t_rcdata *dt, char **map);
void	calculate_wall_dist(t_rcdata *data, char **map);

//parse_maps
void	set_map(t_maps *lvl, char *str, int fd[2]);
void	set_floor_ceiling(int fl_ce[3], char *str);
void	fill_maps(t_maps *lvl, char *str, int fd[2]);
int		get_maps(t_cube *cube, char *file);

//utils.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	free_and_gnl(char **str, int fd);
int		new_img(t_cube *cube, t_data *new_img, int width, int height);
void	free_maps(char **maps, int ind);
void	free_cube(t_cube *cube);

#endif
