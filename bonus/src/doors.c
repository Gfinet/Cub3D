/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:17:19 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/22 16:56:14 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

t_data	data_img(char *file, t_cube *c)
{
	t_data	new;

	new.img = mlx_xpm_file_to_image(c->mlx, file, &new.width, &new.height);
	if (!new.img)
		printf("%s\n", file);
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel,
			&new.line_length, &new.endian);
	return (new);
}

void load_door_texture(t_cube *cube)
{
	(*cube).door_texture[0] = data_img("./texture/door_closed.xpm", cube);
	printf("%i, %i, %s\n", cube->door_texture[0].height, cube->door_texture[0].width, cube->door_texture[0].addr);
	(*cube).door_texture[1] = data_img("./texture/door_half_closed.xpm", cube);
	printf("%i, %i, %s\n", cube->door_texture[1].height, cube->door_texture[1].width, cube->door_texture[1].addr);
	(*cube).door_texture[2] = data_img("./texture/door_half_opened.xpm", cube);
	printf("%i, %i, %s\n", cube->door_texture[2].height, cube->door_texture[2].width, cube->door_texture[2].addr);
	(*cube).door_texture[3] = data_img("./texture/door_open.xpm", cube);
	printf("%i, %i, %s\n", cube->door_texture[3].height, cube->door_texture[3].width, cube->door_texture[3].addr);
}

t_door	*init_new_door(int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	door->open = 0;
	door->on_going = 0;
	door->coord = (t_point){x, y};
	door->next = NULL;
	return (door);
}

void	get_all_doors(char **map, t_cube *c)
{
	int	x;
	int	y;
	// t_door	*door;

	y = -1;
	(*c).doors = 0;
	while (++y < c->lvl->m_height)
	{
		x = -1;
		while (++x < c->lvl->max_len)
			if (map[y][x] == 'D')
				ft_lstadd_back((t_list **)&c->doors, (t_list *)init_new_door(x, y));
	}
	// (*c).doors = door;
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

// * dans raycast:
// pour la fonction "check_wall_dist" modifier la cond hit value pour incorporer '1' et 'D' (ouverte ou fermé)
// pour la fonction draw_wall trouver un moyen de choisir la bonne texture en fonction de si porte ou pas >> pe separer la fonction pour
// choisir celle ci d'abord avant de dessiner 
// si porte est on_going, l'incrementer ou decrementer pour arriver a l'autre
