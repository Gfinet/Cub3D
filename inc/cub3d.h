/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:41:55 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/01 17:57:11 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "keycode.h"
# include "../inc/Printf/ft_printf.h"
# include "../inc/minilibx/mlx.h"

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 800
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1200
# endif

// typedef struct s_mouse_type
// {
// 	mouse_key_t mcode;
// 	action_t act;
// 	modifier_key_t key;
// 	void *cube;
// }	t_mouse_type;

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

#endif
