/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:41:55 by gfinet            #+#    #+#             */
/*   Updated: 2024/08/17 17:48:50 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "keycode.h"
# include "../inc/Printf/ft_printf.h"
# include "../inc/minilibx/mlx.h"
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
# define LST_CHAR "012NSEW"

typedef struct s_mlx
{
	void		*appid;
	void		*win_list;
	void		*img_list;
	void		(*loop_hook)(void *);
	void		*loop_hook_data;
	void		*loop_timer;
	void		*font;
	int			main_loop_active;
}	t_mlx;

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
	char		*c_text[4];
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

typedef struct s_cube
{
	void		*mlx;
	void		*win;
	t_maps		*lvl;
	t_data		texture[4];
	t_player	*player;
	t_data		*screen;
	int			frame;
}	t_cube;

typedef struct s_rcdata
{
	t_point			delta_dist;
	t_point			side_dist;
	t_point			ray_dir;
	t_point			step;
	t_point			plane;
	t_point			dest;
	int				side;
	int				hit;
	double			camerx;
	double			perp_wall_dist;
}	t_rcdata;

typedef struct s_drawdata
{
	int				tex_x;
	int				tex_y;
	int				line_height;
	int				pitch;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	double			step_f;
}	t_drawdata;

//handle_event.c
int		esc_handle(t_cube *cube);
int		key_event(int keycode, t_cube *cube);
int		key_event_release(int keycode, t_cube *cube);
int		mouse_event(int mcode, int x, int y, t_cube *cube);
int		fps(t_cube	*cube);

//parse_maps.c
int		get_maps(t_cube *cube, char *file);
void	fill_maps(t_maps *lvl, char *str, int fd[2]);
void	set_floor_ceiling(int fl_ce[3], char *str);
void	set_map(t_maps *lvl, char *str, int fd[2]);

//check_maps.c
int		check_map(t_cube *cube);
int		in_char_lst(char c);

//check_arg
int		check_arg(t_cube *cube, char *file);
int		check_elem(char *file);
int		check_line(char *str);
char	*get_text_dir(char *str);
int		get_dir(char *str);

//interations
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

//raycast
void	rcdda(t_cube *cube, char **map, t_player player);
void	set_dda_ray_delta(t_rcdata *data, t_player player, int x);
void	set_side_dist_and_step(t_player p, t_rcdata *dt);
void	calculate_wall_dist(t_rcdata *data, char **map);

//movements
void	turn(t_cube *cube, double angle, int frame);
void	update_player(t_cube *cube, t_player *player);

//utils
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	free_and_gnl(char **str, int fd);
int		new_img(t_cube *cube, t_data *new_img, int width, int height);
void	free_maps(char **maps, int ind, int f);
void	free_cube(t_cube *cube);

#endif
