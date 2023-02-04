/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:55:45 by doykim            #+#    #+#             */
/*   Updated: 2023/02/04 16:53:40 by sanghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int key, t_game *game)
{
    if (key == KEY_W)
    {
        if (game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_x * game->movespeed)] == '0')
            game->player.x += game->player.dir_x * game->movespeed;
        if (game->map[(int)(game->player.y + game->player.dir_y * game->movespeed)][(int)(game->player.x)] == '0')
            game->player.y += game->player.dir_y * game->movespeed;
    }

    if (key == KEY_S)
    {
        if (game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_x * game->movespeed)] == '0')
            game->player.x -= game->player.dir_x * game->movespeed;
        if (game->map[(int)(game->player.y + game->player.dir_y * game->movespeed)][(int)(game->player.x)] == '0')
            game->player.y -= game->player.dir_y * game->movespeed;
    }
    if (key == KEY_A)
    {
        if (game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_x * game->movespeed)] == '0')
            game->player.x -= game->plane_x * game->movespeed;
        if (game->map[(int)(game->player.y + game->player.dir_y * game->movespeed)][(int)(game->player.x)] == '0')
            game->player.y -= game->plane_y * game->movespeed;
    }
    if (key == KEY_D)
    {
        if (game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_x * game->movespeed)] == '0')
            game->player.x += game->plane_x * game->movespeed;
        if (game->map[(int)(game->player.y + game->player.dir_y * game->movespeed)][(int)(game->player.x)] == '0')
            game->player.y += game->plane_y * game->movespeed;
    }
    if (key == KEY_LEFT)
    {
        double oldDirectionX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-game->rotspeed) - game->player.dir_y * sin(-game->rotspeed);
        game->player.dir_y = oldDirectionX * sin(-game->rotspeed) + game->player.dir_y * cos(-game->rotspeed);
        double oldPlaneX = game->plane_x;
        game->plane_x = game->plane_x * cos(-game->rotspeed) - game->plane_y * sin(-game->rotspeed);
        game->plane_y = oldPlaneX * sin(-game->rotspeed) + game->plane_y * cos(-game->rotspeed);
    }
    if (key == KEY_RIGHT)
    {
        double oldDirectionX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(game->rotspeed) - game->player.dir_y * sin(game->rotspeed);
        game->player.dir_y = oldDirectionX * sin(game->rotspeed) + game->player.dir_y * cos(game->rotspeed);
        double oldPlaneX = game->plane_x;
        game->plane_x = game->plane_x * cos(game->rotspeed) - game->plane_y * sin(game->rotspeed);
        game->plane_y = oldPlaneX * sin(game->rotspeed) + game->plane_y * cos(game->rotspeed);
    }
    if (key == KEY_ESC)
        exit(0);
    main_loop(game);
    return (0);
}
