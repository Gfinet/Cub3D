/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/08/28 00:54:02 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_format(char *file)
{
	size_t	i;

	i = ft_strlen(file);
	while (file && i && file[i] != '.')
		i--;
	if (!file || ft_strncmp(&file[i], ".cub", 5))
		return (0);
	return (1);
}

static int	init_cube(t_cube *cube, t_player *play, t_maps *level)
{
	*cube = (t_cube){0};
	*play = (t_player){0};
	*level = (t_maps){0};
	cube->mlx = mlx_init();
	cube->frame = FRAME;
	if (!cube->mlx)
		return (0);
	cube->win = mlx_new_window(cube->mlx, WIN_WIDTH, WIN_HEIGHT, "DOOM3D");
	if (!cube->win)
		return (0);
	cube->screen = malloc(sizeof(t_data));
	if (!cube->screen)
		return (0);
	*(cube->screen) = (t_data){0};
	cube->lvl = level;
	cube->player = play;
	return (1);
}

static int	get_textures(t_cube *cube)
{
	int		i;
	t_data	*txt;

	txt = cube->texture;
	i = -1;
	while (++i < 4)
	{
		txt[i].img = mlx_xpm_file_to_image(cube->mlx, cube->lvl->c_text[i],
				&txt[i].width, &txt[i].height);
		if (!txt[i].img)
			return (-i);
		txt[i].addr = mlx_get_data_addr(txt[i].img, &txt[i].bits_per_pixel,
				&txt[i].line_length, &txt[i].endian);
	}
	if (!new_img(cube, cube->screen, WIN_WIDTH, WIN_HEIGHT))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cube		cube;
	t_maps		level;
	t_player	player;

	if (argc != 2)
		return (write(2, ERROR_ARG, 14), 0);
	if (!check_format(argv[1]))
		return (write(2, ERROR_FRM, 17), 0);
	if (!init_cube(&cube, &player, &level))
		return (write(2, ERROR_MAL, 19), free_cube(&cube), 0);
	if (!get_maps(&cube, argv[1]))
		return (write(2, ERROR_MAP, 15), free_cube(&cube), 0);
	if (!get_textures(&cube))
		return (write(2, ERROR_TXT, 19), free_cube(&cube), 0);
	if (!make_mini(&cube, &level))
		return (write(2, ERROR_MMP, 34), free_cube(&cube), 0);
	draw_doom(&cube);
	mlx_loop_hook(cube.mlx, &fps, &cube);
	mlx_hook(cube.win, 17, 0, &esc_handle, &cube);
	mlx_hook(cube.win, 2, 0, &key_event, &cube);
	mlx_hook(cube.win, 3, 10, &key_event_release, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
