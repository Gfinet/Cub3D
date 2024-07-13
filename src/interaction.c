/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:12:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/13 15:31:16 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_not_wallz(t_cube *c, t_point new_p, t_player *pl)
{
	double	n_x;
	double	n_y;
	double	rad;

	rad = (90) * (M_PI / 180.0);
	n_x = (pl->dir.x * cos(-rad)) - (pl->dir.y) * sin(-rad);
	n_y = pl->dir.x * sin(-rad) + (pl->dir.y) * cos(-rad);
	if (pl->move_v && (c->maps->c_maps[(int)pl->pos.y][(int)(new_p.x
			+ (pl->move_v * 0.15 * pl->dir.x))] == '1'
		|| c->maps->c_maps[(int)(new_p.y + (pl->move_v * 0.15 * pl->dir.y))]
		[(int)pl->pos.x] == '1'))
		return (0);
	if (pl->move_h && (c->maps->c_maps[(int)pl->pos.y][(int)(new_p.x
			+ pl->move_h * 0.15 * n_x)] == '1' || c->maps->c_maps[(int)(new_p.y
		+ pl->move_h * 0.15 * n_y)][(int)pl->pos.x] == '1'))
		return (0);
	return (1);
}
