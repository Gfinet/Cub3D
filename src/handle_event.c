/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:04:25 by gfinet            #+#    #+#             */
/*   Updated: 2024/06/29 13:05:34 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	esc_handle(void *param)
{
	t_cube *cube;

	cube = param;
	if (cube)
		mlx_close_window(cube->mlx);
	exit(0);
}

void	key_event(mlx_key_data_t keydata, void *param)
{
	t_cube *cube;

	cube = param;
	if (keydata.key == 256)
		esc_handle(param);
	printf("key = %d\n", keydata.key);
}

void mouse_event(mouse_key_t button, action_t action, modifier_key_t mods,void *param)
{
	// button : L 0, R 1, MID 2
	//action rien 0, press, 1
	// mods :
	// MLX_SHIFT		= 0x0001,
	// MLX_CONTROL		= 0x0002,
	// MLX_ALT			= 0x0004,
	t_cube *cube;

	cube = param;
	printf("%d %d %d\n", button, action, mods);
}

void scroll_event(double xdelta, double ydelta, void* param)
{
	// y : "puissance du scroll"
	// x : swipe vers gauche/droite ?
	t_cube *cube;

	cube = param;
	printf("x : %f, y : %f\n", xdelta, ydelta);
}

void add_event(void *param)
{
	t_cube *cube;

	cube = param;
	printf("add_event\n");
}