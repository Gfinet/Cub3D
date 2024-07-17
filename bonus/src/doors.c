/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:17:19 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/17 22:13:10 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

t_data	data_img(char *file, t_cube *c)
{
	t_data	new;

	new.img = mlx_xpm_file_to_image(c->mlx, file, &new.width, &new.height);
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel,
			&new.line_length, &new.endian);
	return (new);
}

void load_door_texture(t_cube *cube)
{
	cube->door_texture[0] = data_img("./texture/door_closed", cube);
	cube->door_texture[1] = data_img("./texture/door_half_closed", cube);
	cube->door_texture[2] = data_img("./texture/door_half_opened", cube);
	cube->door_texture[3] = data_img("./texture/door_open", cube);
}

t_door	*init_new_door(int x, int y)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	door->open = 0;
	door->on_going = 0;
	door->coord = (t_point){x, y};
	door->next = NULL;
}


// appeler init_new_door dans checker_map lorsqu'on tombe sur 'P' et appeler lst_addback pour ajouter la porte a la liste;

// * dans raycast:
// pour la fonction "check_wall_dist" modifier la cond hit value pour incorporer '1' et 'P' (ouverte ou fermé)
// pour la fonction draw_wall trouver un moyen de choisir la bonne texture en fonction de si porte ou pas >> pe separer la fonction pour
// choisir celle ci d'abord avant de dessiner 
// si porte est on_going, l'incrementer ou decrementer pour arriver a l'autre

// * dans interaction
// ajouter porte comme coll >> serait referable de faire une fonction qui reconnait si l'input est passable ou pas 
// (i.e porte non ouverte / mur / mirroir)
// reconnaitre la porte dans la liste en fct des coords de celle-ci

// * dans events
// ajouter la key_press/release (a voir) pour ouvrir / fermer la porte >> passer on_going a 1