/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:00 by sanghan           #+#    #+#             */
/*   Updated: 2023/02/08 13:28:19 by doykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void verLine (t_game *game, int x, int y1, int y2, int color)
{
    int temp;

    temp = y1;
	while (temp <= y2)
    {
        mlx_pixel_put(game->mlx, game->win, x, temp, color);
        temp++;
    }
}

int raycasting(t_game *game)
{
    game->image->data = (int *)mlx_get_data_addr(game->image->img, &(game->image->bpp), \
        &(game->image->line_len), &(game->image->endian));

    
    int x;

    x = 0;
    while (x < WIDTH)
    {
        double cameraX = (2 * x / (double)(WIDTH)) - 1;
		
		double rayDirectionX = game->player.dir_x + game->plane_x * cameraX;
		double rayDirectionY = game->player.dir_y + game->plane_y * cameraX;
		
		int mapX = (int)(game->player.x);
		int mapY = (int)(game->player.y);

        double sideDistX;
        double sideDistY;

        double deltaDistX;
        if (rayDirectionX != 0)
            deltaDistX = fabs(1 / rayDirectionX);
        double deltaDistY;
        if (rayDirectionY != 0)
            deltaDistY = fabs(1 / rayDirectionY);

        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

		if (rayDirectionX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
        }
        if (rayDirectionY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
        }

        mapX = game->player.x;
        mapY = game->player.y;
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
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
			}
			////////////////////////////////
            if (game->map[mapY][mapX] == '1')
                hit = 1;
        }
        if (side == 0)
            perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / rayDirectionX;
        else
            perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / rayDirectionY;



        //
        t_img	texture_img;
        int textureX;
        int textureY;

        if (side == 1 && stepY < 0)
            texture_img = game->img_no;
        else if (side == 1)
            texture_img = game->img_so;
        else if (stepX > 0)
            texture_img = game->img_ea;
        else
            texture_img = game->img_we;


        //calc line
        double wallX;

        if (side == 0)
            wallX = game->player.y + perpWallDist * rayDirectionY;
        else
            wallX = game->player.x + perpWallDist * rayDirectionX;
        wallX -= floor(wallX);
        textureX = (int)(wallX * (double)texture_img.line_len / 4);
        if (side == 0 && rayDirectionX < 0)
            textureX = texture_img.line_len / 4 - textureX - 1;
        if (side == 1 && rayDirectionY > 0)
            textureX = texture_img.line_len / 4 - textureX - 1;

        //

        int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = (-lineHeight / 2) + (HEIGHT / 2);
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = (lineHeight / 2) + (HEIGHT / 2);
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT;

        double step;
        double texture_pos;
        step = (double)texture_img.line_len / 4 / lineHeight;
        texture_pos = (drawStart - HEIGHT / 2 + \
		lineHeight / 2) * step;


        int	y;
        int	pixel;

        y = 0;
		while (y < HEIGHT)
        {
            pixel = (y * game->image->line_len / 4) + x;
			if (y < drawStart)
				game->image->data[pixel] = game->ceil;
			else if (y < drawEnd)
			{
            textureY = (int)texture_pos \
                & (texture_img.line_len / 4 - 1);
            game->image->data[pixel] = \
                texture_img.data[textureY * texture_img.line_len / 4 + \
                textureX];
            texture_pos += step;
			}
			else
				game->image->data[pixel] = game->floor;
			y++;
        }
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
	return(0);
}
