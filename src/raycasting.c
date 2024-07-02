/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:08:02 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/02 17:34:07 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_data*	rcdda(t_cube *cube, char **map, t_player player)
{
	t_data			*screen;
	t_point			delta_dist;
	t_point			side_dist;
	t_point			ray_dir;
	t_point			step;
	t_point			plane;
	t_point			dest;
	double			cameraX;
	double			perp_wall_dist;
	int				x;
	int				hit = 0;
	int				side = 0;
	int				line_height = 0;
	int				pitch = 0;
	int				draw_start = 0;
	int				draw_end = 0;
	int				tex_num = 0;
	double			wall_x = 0;
	int				tex_x = 0;
	int				tex_y = 0;
	double			step_f = 0;
	double			tex_pos = 0;
	double			tex_width = 0;
	double			tex_weight = 0;
	unsigned int	color = 0;

	screen = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	plane.x = 0.66;
	plane.y = 0;
	x = -1;
	while (++x < WIN_WIDTH)
	{
		cameraX = 2 * x / ((double)WIN_WIDTH) - 1; //x-coordinate in camera space
    	printf("CX >>>>> %f\n", cameraX);
		ray_dir.x = player.dir.x + plane.x * (cameraX);
    	ray_dir.y = player.dir.y + plane.y * (cameraX);
		printf("ray y >> %f, ray x >> %f\n", ray_dir.y, ray_dir.x);
		if (ray_dir.x)
			delta_dist.x = fabs(1 / ray_dir.x);
		else
			delta_dist.x = 1e30;
		if (ray_dir.y)
			delta_dist.y = fabs(1 / ray_dir.y);
		else
			delta_dist.x = 1e30;
		dest = (t_point){(int)player.pos.x, (int)player.pos.y};
		if(ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (player.pos.x - dest.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (dest.x + 1.0 - player.pos.x) * delta_dist.x;
		}
		if(ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (player.pos.y - dest.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (dest.y + 1.0 - player.pos.y) * delta_dist.y;
		}
		hit = 0;
		while (hit == 0)
		{
			if(side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				dest.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				dest.y += step.y;
				side = 1;
			}
			if(map[(int)dest.y][(int)dest.x] == '1')
				hit = 1;
		}
		printf("hit y >> %i, hit x >> %i\n", (int)dest.y, (int)dest.x);
		if(side == 0)
			perp_wall_dist = (side_dist.x - delta_dist.x);
		else
			perp_wall_dist = (side_dist.y - delta_dist.y);
		//Calculate height of line to draw on screen
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		pitch = 100;

		//calculate lowest and highest pixel to fill in current stripe
		draw_start = -line_height / 2 + WIN_HEIGHT / 2 + pitch;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2 + pitch;
		if(draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;

		//texturing calculations
		tex_num = map[(int)dest.y][(int)dest.x] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wall_x
		if(side == 0)
			wall_x = player.pos.x + perp_wall_dist * ray_dir.y;
		else
			wall_x = player.pos.y + perp_wall_dist * ray_dir.x;
		wall_x -= floor((wall_x));

		//x coordinate on the texture
		tex_x = (int)(wall_x * (double)(tex_width));
		if(side == 0 && ray_dir.x > 0)
			tex_x = tex_width - tex_x - 1;
		if(side == 1 && ray_dir.y < 0)
			tex_x = tex_width - tex_x - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		step_f = 1.0 * tex_weight / line_height;
		// Starting texture coordinate
		tex_pos = (draw_start - pitch - WIN_HEIGHT / 2 + line_height / 2) * step_f;
		int y = draw_start - 1;
		// ft_printf("out >>> %i, %i ; draw end = %i\n", x, y, draw_end);
		while(++y < draw_end)
		{
		  // Cast the texture coordinate to integer, and mask with (tex_weight - 1) in case of overflow
		  tex_y = (int)tex_pos & (int)(tex_weight - 1);
		  tex_pos += step_f;
		  color = (unsigned int)cube->texture->addr+(((int)tex_weight * tex_y + tex_x));
		  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		  if(side == 1)
		  	color = (color >> 1) & 8355711;
		// ft_printf("%i, %i\n", x, y);
		mlx_pixel_put(cube->mlx, cube->win, x, y, color);
		my_mlx_pixel_put(screen, x, y, color);
		// screen->buffer[y * WIN_WIDTH + x] = color;
		}
	}
	return screen;
}
/*  while(!done())
  {
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX*cameraX;
      double rayDirY = dirY + planeY*cameraX;

      //which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);


      int pitch = 100;

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2 + pitch;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2 + pitch;
      if(drawEnd >= h) drawEnd = h - 1;

      //texturing calculations
      int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = posY + perpWallDist * rayDirY;
      else          wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
    }*/