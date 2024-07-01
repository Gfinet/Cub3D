/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/01 16:03:59 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int check_format(char *file)
{
	size_t i;

	i = 0;
	while (file && i < ft_strlen(file) && file[i] != '.')
		i++;
	if (ft_strncmp(&file[i], ".cub", 5))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cube cube;
	t_img img;

	img.path = ft_strdup("/Users/gfinet/Desktop/Github/Cub3D/minecraft.xpm");
	img.texture = mlx_load_xpm42(img.path);
	if (argc != 2 )
		return (write(2, "Error\nBad Arg\n", 14), 0);
	if (!check_format(argv[1]))
		return (write(2, "Error\nBad format\n", 17), 0);
	cube.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "DOOM3D", true);
	img.img = mlx_texture_to_image(cube.mlx, &(img.texture->texture));
	mlx_image_to_window(cube.mlx, img.img, 50, 50);
	mlx_key_hook(cube.mlx, key_event, &cube);
	mlx_close_hook(cube.mlx, esc_handle, &cube);
	mlx_mouse_hook(cube.mlx, mouse_event, &cube);
	mlx_scroll_hook(cube.mlx, scroll_event, &cube);
	//mlx_loop_hook(cube.mlx, add_event, &cube);
	mlx_loop(cube.mlx);
	return (0);
}