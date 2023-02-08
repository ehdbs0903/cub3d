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

int raycasting(t_game *game)
{
    t_ray   ray;
    int x;

    game->image->data = (int *)mlx_get_data_addr(game->image->img, &(game->image->bpp), \
        &(game->image->line_len), &(game->image->endian));

    

    x = 0;
    while (x < WIDTH)
    {
        ray.camera_x = (2 * x / (double)(WIDTH)) - 1;
		
		ray.ray_dir_x = game->player.dir_x + game->plane_x * ray.camera_x;
		ray.ray_dir_y = game->player.dir_y + game->plane_y * ray.camera_x;
		
		ray.map_x = (int)(game->player.x);
		ray.map_y = (int)(game->player.y);

        if (ray.ray_dir_x != 0)
            ray.deltadist_x = fabs(1 / ray.ray_dir_x);
        if (ray.ray_dir_y != 0)
            ray.deltadist_y = fabs(1 / ray.ray_dir_y);
        ray.hit = 0;
		if (ray.ray_dir_x < 0)
        {
            ray.step_x = -1;
            ray.sidedist_x = (game->player.x - ray.map_x) * ray.deltadist_x;
        }
        else
        {
            ray.step_x = 1;
            ray.sidedist_x = (ray.map_x + 1.0 - game->player.x) * ray.deltadist_x;
        }
        if (ray.ray_dir_y < 0)
        {
            ray.step_y = -1;
            ray.sidedist_y = (game->player.y - ray.map_y) * ray.deltadist_y;
        }
        else
        {
            ray.step_y = 1;
            ray.sidedist_y = (ray.map_y + 1.0 - game->player.y) * ray.deltadist_y;
        }
//dda
        ray.map_x = game->player.x;
        ray.map_y = game->player.y;
        while (ray.hit == 0)
        {
            if (ray.sidedist_x < ray.sidedist_y)
            {
                ray.sidedist_x += ray.deltadist_x;
                ray.map_x += ray.step_x;
				ray.side = 0;
			}
            else
            {
                ray.sidedist_y += ray.deltadist_y;
                ray.map_y += ray.step_y;
                ray.side = 1;
			}
            if (game->map[ray.map_y][ray.map_x] == '1')
                ray.hit = 1;
        }

//calculate_perp_wall_dist

        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - game->player.x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - game->player.y + (1 - ray.step_y) / 2) / ray.ray_dir_y;


// set wall
        t_img	texture_img;

        if (ray.side == 1 && ray.step_y < 0)
            texture_img = game->img_no;
        else if (ray.side == 1)
            texture_img = game->img_so;
        else if (ray.step_x > 0)
            texture_img = game->img_ea;
        else
            texture_img = game->img_we;


// calculate_line
        if (ray.side == 0)
            ray.wall_x = game->player.y + ray.perp_wall_dist * ray.ray_dir_y;
        else
            ray.wall_x = game->player.x + ray.perp_wall_dist * ray.ray_dir_x;
        ray.wall_x -= floor(ray.wall_x);


        ray.texture_x = (int)(ray.wall_x * (double)texture_img.line_len / 4);
        if (ray.side == 0 && ray.ray_dir_x < 0)
            ray.texture_x = texture_img.line_len / 4 - ray.texture_x - 1;
        if (ray.side == 1 && ray.ray_dir_y > 0)
            ray.texture_x = texture_img.line_len / 4 - ray.texture_x - 1;



        int lineHeight = (int)(HEIGHT / ray.perp_wall_dist);

		ray.drawstart = (-lineHeight / 2) + (HEIGHT / 2);
        if (ray.drawstart < 0)
            ray.drawstart = 0;
        ray.drawend = (lineHeight / 2) + (HEIGHT / 2);
        if (ray.drawend >= HEIGHT)
            ray.drawend = HEIGHT;
        ray.step = (double)texture_img.line_len / 4 / lineHeight;
        ray.texture_pos = (ray.drawstart - HEIGHT / 2 + \
		lineHeight / 2) * ray.step;


        int	y;
        int	pixel;
//draw img
        y = 0;
		while (y < HEIGHT)
        {
            pixel = (y * game->image->line_len / 4) + x;
			if (y < ray.drawstart)
				game->image->data[pixel] = game->ceil;
			else if (y < ray.drawend)
			{
            ray.texture_y = (int)ray.texture_pos \
                & (texture_img.line_len / 4 - 1);
            game->image->data[pixel] = \
                texture_img.data[ray.texture_y * texture_img.line_len / 4 + \
                ray.texture_x];
            ray.texture_pos += ray.step;
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
