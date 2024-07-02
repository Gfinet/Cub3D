/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:41:55 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/02 15:40:30 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "keycode.h"
# include "../inc/Printf/ft_printf.h"
# include "../inc/minilibx/mlx.h"

# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 640 //1280
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1200 //2400
# endif

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mini_maps
{
	t_data maps;
	int witdh;
	int height;
}	t_mini_maps;

typedef struct s_maps
{
	t_mini_maps mini;
	char **c_maps;
	char *no_text;
	char *so_text;
	char *we_text;
	char *ea_text;
	int max_len;
	int floor[3];
	int ceiling[3];
	int m_height;

}	t_maps;

typedef struct s_cube
{
	//mlx_t		*mlx_w;
	void		*mlx;
	void		*win;
	//mlx_image_t	***all_img;

}	t_cube;


typedef struct s_img
{
	void *img;
	//xpm_t *texture;
	char *path;
	int witdh;
	int height;
	
}	t_img;

//handle_event.c
int	esc_handle(t_cube *cube);
int	key_event(int keycode, t_cube *cube);
int	mouse_event(int mcode, int x, int y, t_cube *cube);
int	scroll_event(double xdelta, double ydelta, t_cube *cube);
int	add_event(t_cube *cube);

//parse_maps.c
int get_maps(t_maps *lvl, char *file);
void fill_maps(t_maps *lvl, char *str, int fd[2]);
void set_floor_ceiling(int fl_ce[3], char *str);
void set_map(t_maps *lvl, char *str, int fd[2]);

//check_maps.c
int check_map(char *file);

int make_mini(t_cube *cube, t_maps *lvl);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_mini_pixel(t_maps *lvl, int w_h[2], int i[2]);
#endif
