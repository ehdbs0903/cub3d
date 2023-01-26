/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:00 by sanghan           #+#    #+#             */
/*   Updated: 2023/01/26 18:15:06 by sanghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(t_game *game, int x, int y);
void	draw1(t_game *game, int x, int y);
void	draw2(t_game *game, int x, int y);

void raycasting(t_game *game)
{
	int		x = 0;
	double cameraX = 0;
	double	rayDirx = 0;
	double	rayDiry = 0;
	int		mapX = 0;
	int		mapY = 0;
	//length of ray from current position to next x or y-side
	double	sideDistX = 0;
	double	sideDistY = 0;
	double	deltaDistX = 0;
	double 	deltaDistY = 0;
	int		hit = 0;
	int		stepX = 0;
	int		stepY = 0;
	int		side = 0;
	double	perpWallDist = 0;

	x = 0;
	hit = 0;
	while (x < WIDTH)
	{
		//calculate ray position and direction
		cameraX = 2 * x / WIDTH - 1;
		rayDirx = game->player.dir_x + game->plane_x * cameraX;
		rayDiry = game->player.dir_y + game->plane_y * cameraX;

		mapX = (int)game->player.x;
		mapY = (int)game->player.y;
		if (rayDirx != 0)
			deltaDistX = fabs(1 / rayDirx);
		if (rayDiry != 0)
			deltaDistY = fabs(1 / rayDiry);
		hit = 0;
		if (rayDirx < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
		}
		if (rayDirx < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y - mapY) * deltaDistX;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistX;
				mapY += stepY;
				side = 1;
			}
			if (game->map[mapX][mapY] > '0')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / rayDirx;
		else
			perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / rayDiry;
		//set_wall
		// t_img	texture_img;

		// if (side == 1 && stepY < 0)
		// 	texture_img = game->img_no;
		// else if (side == 1)
		// 	texture_img = game->img_so;
		// else if (stepX > 0)
		// 	texture_img = game->img_ea;
		// else
		// 	texture_img = game->img_we;

		// double wall_x;
		// double wall_y;

		// if (side == 0)
		// 	wall_x = game->player.y + perpWallDist* rayDiry;
		// else
		// 	wall_x = game->player.x + perpWallDist * rayDirx;
		// wall_x -= floor(wall_x);
		// texture_x = (int)(ray->wall_x * \
		// 	(double) texture_img->line_bytes / 4);
		// if (ray->side == 0 && ray->ray_dir_x > 0)
		// 	ray->texture_x = texture_img->line_bytes / 4 - ray->texture_x - 1;
		// if (ray->side == 1 && ray->ray_dir_y < 0)
		// 	ray->texture_x = texture_img->line_bytes / 4 - ray->texture_x - 1;
		// ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
		// ray->draw_start = -1 * ray->line_height / 2 + WIN_HEIGHT / 2;
		// if (ray->draw_start < 0)
		// 	ray->draw_start = 0;
		// ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
		// if (ray->draw_end >= WIN_HEIGHT)
		// 	ray->draw_end = WIN_HEIGHT;
		// ray->step = (double) texture_img->line_bytes / 4 / ray->line_height;
		// ray->texture_pos = (ray->draw_start - WIN_HEIGHT / 2 + \
		// 	ray->line_height / 2) * ray->step;
		//lineHeight

		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		//t_rgb color;
		//printf("!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		//draw_rectangle(game, mapX, mapY);
// 		switch (game->map[mapX][mapY])
// 		{
// 			//case 1:  color.r = 0, color.g =  255, color.b = 0;  break; //red
// 			case '1': draw1(game, mapX, mapY);
// //			default: color.r = 0, color.g =  255, color.b = 255; break; //yellow
// 			default: draw2(game, mapX, mapY);
// 		}
		// if (side == 1)
		// {
		// 	color.r = color.r / 2;
		// 	color.b = color.b / 2;
		// 	color.g = color.g / 2;
		// }
		x++;
	}
}

// void	draw1(t_game *game, int x, int y)
// {
// 	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
// 	for (int i = x ; i < x + 10 ; i++)
// 	{
// 		for (int j = y ; j < y + 10 ; j++)
// 		{
// 			mlx_pixel_put (game->mlx, game->win, i, j, 0x00000000);
// 		}
// 	}
// }

// void	draw2(t_game *game, int x, int y)
// {
// 	printf("###############################\n");
// 	for (int i = x ; i < x + 10 ; i++)
// 	{
// 		for (int j = y ; j < y + 10 ; j++)
// 		{
// 			mlx_pixel_put (game->mlx, game->win, i, j, 0x00FFFFFF);
// 		}
// 	}
// }
//mlx_pixel_put (game.mlx, game.win, i, j, 0x00FFFFFF);
// void	draw_rectangle(t_game *game, int x, int y)
// {
// 	int i;
// 	int j;

// 	x *= TILE_SIZE;
// 	y *= TILE_SIZE;
// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			game->img.data[(y  + i) * WIDTH + x + j] = 0xFFFFFF;
// 			j++;
// 		}
// 		i++;
// 	}
// }
// 			game->img.data[(y + i) * WIDTH + x + j] = 0xFFFFFF;
// 			image.data[i * image.line_len / 4 + j] = rgb;

	//mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
			//length of ray from one x or y-side to next x or y-side

//			int side; //was a NS or a EW wall hit?

	//calculate step and initial sideDist
/*
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(1080 / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + 1080 / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + 1080 / 2;
			if(drawEnd >= 1080)drawEnd = 1080 - 1;

			t_rgb color;
			switch(game->map[mapX][mapY])
			{
				case 1:  color.r = 255, color.g =  0, color.b = 0;  break; //red
				case 2:  color.r = 0, color.g =  255, color.b = 0;  break; //green
				case 3:  color.r = 0, color.g =  0, color.b = 255;   break; //blue
				case 4:  color.r = 255, color.g =  255, color.b = 255;  break; //white
				default: color.r = 0, color.g =  255, color.b = 255; break; //yellow
			}
			//give x and y sides different brightness
			if (side == 1)
			{
				color.r = color.r / 2;
				color.b = color.b / 2;
				color.g = color.g / 2;
			}
			//draw the pixels of the stripe as a vertical line
			//verLine(x, drawStart, drawEnd, color); 수직선
		}
	oldTime = time;
*/

//	time = getTicks();
//	double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
//	print(1.0 / frameTime); //FPS counter
//	redraw();
//	cls();

	//speed modifiers
//	double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
//	double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
//	readKeys();

/*
	//move forward if no wall in front of you


	if (keyDown(KEY_W))
	{
		if(game->map[(int)(posX + dirX * moveSpeed)][(int)posY] == false) posX += dirX * moveSpeed;
		if(game->map[(int)(posX)][(int)(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (keyDown(KEY_S))
	{
		if(game->map[(int)(posX - dirX * moveSpeed)][(int)(posY)] == false) posX -= dirX * moveSpeed;
		if(game->map[(int)(posX)][(int)(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}

	//rotate to the right
	if (keyDown(SDLK_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (keyDown(SDLK_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	*/
