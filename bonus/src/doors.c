/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:17:19 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/25 13:44:12 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

t_data	data_img(char *file, t_cube *c)
{
	t_data	new;

	new.img = mlx_xpm_file_to_image(c->mlx, file, &new.width, &new.height);
	if (!new.img)
		return ((t_data){0});
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel,
			&new.line_length, &new.endian);
	return (new);
}

void	load_door_texture(t_cube *cube)
{
	(*cube).door_texture[0] = data_img("./texture/door_closed.xpm", cube);
	if (!cube->texture[0].img)
		esc_handle(cube);
	(*cube).door_texture[1] = data_img("./texture/door_half_opened.xpm", cube);
	if (!cube->texture[1].img)
		esc_handle(cube);
	(*cube).door_texture[2] = data_img("./texture/door_open.xpm", cube);
	if (!cube->texture[2].img)
		esc_handle(cube);
}

t_door	*init_new_door(int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	if (!door)
		return (0);
	door->open = 0;
	door->on_going = 0;
	door->coord = (t_point){x, y};
	door->next = NULL;
	return (door);
}

void	get_all_doors(char **map, t_cube *c)
{
	int		x;
	int		y;
	t_door	*door;

	y = -1;
	(*c).doors = 0;
	door = NULL;
	while (++y < c->lvl->m_height)
	{
		x = -1;
		while (++x < c->lvl->max_len)
		{
			if (map[y][x] == 'D')
			{
				door = init_new_door(x, y);
				if (!door)
					esc_handle(c);
				ft_lstadd_back((t_list **)&c->doors, (t_list *)door);
			}
		}
	}
}

t_door	*find_door(t_cube *c, float x, float y)
{
	t_door	*door;

	door = c->doors;
	while (door)
	{
		if (fabs(door->coord.x - x) <= 1 && fabs(door->coord.y - y) <= 1)
			break ;
		door = door->next;
	}
	return (door);
}
