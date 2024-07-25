/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:36:22 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/25 16:48:56 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int mouse_other_event(int butt, int x, int y, t_cube *cube)
{
	if (butt == MS_DW)
		cube->player->use_weap--;
	if (butt == MS_UP)
		cube->player->use_weap++;
	if (cube->player->use_weap <= 0)
		cube->player->use_weap = cube->lvl->nb_weap - 1;
	else if (cube->player->use_weap >= cube->lvl->nb_weap - 1)
		cube->player->use_weap = 0;
	printf("%d %d %d %p\n", butt, x, y, cube);
	printf("%d\n", cube->player->use_weap);
	return (1);
}