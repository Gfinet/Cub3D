/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:41:55 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/01 15:56:20 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "keycode.h"
# include "../Printf/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 800
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1200
# endif

typedef struct s_mouse_type
{
	mouse_key_t mcode;
	action_t act;
	modifier_key_t key;
	void *cube;
}	t_mouse_type;

typedef struct s_cube
{
	//mlx_t		*mlx_w;
	void		*mlx;
	void		*win;
	mlx_image_t	***all_img;

}	t_cube;


typedef struct s_img
{
	void *img;
	xpm_t *texture;
	char *path;
	int witdh;
	int height;
	
}	t_img;

//handle_event.c
void	esc_handle(void *f);
void	key_event(mlx_key_data_t keydata, void *f);
void	mouse_event(mouse_key_t button, action_t action, modifier_key_t mods, void *cube);
void	scroll_event(double xdelta, double ydelta, void* param);
void	add_event(void *param);

#endif
