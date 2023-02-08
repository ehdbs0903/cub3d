/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:52:43 by doykim            #+#    #+#             */
/*   Updated: 2023/02/08 12:36:12 by doykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_ws(t_game *game, int flag)
{
	// double	npos_x;
	// double	npos_y;

	// npos_x = game->player.x + game->player.dir_x * game->movespeed * flag;
	// npos_y = game->player.y + game->player.dir_y * game->movespeed * flag;
	// if (game->map[(int)npos_y][(int)npos_y] == '1')
	// 	return ;
	// game->player.x = npos_x;
	// game->player.y = npos_y;

	double	move_x;
	double	move_y;

	move_x = game->player.x + game->player.dir_x * game->movespeed * flag;
	move_y = game->player.y + game->player.dir_y * game->movespeed * flag;
	if (game->map[(int)move_y][(int)move_x] == '1')
		return ;
	game->player.x = move_x;
	game->player.y = move_y;
}

void	key_ad(t_game *game, int flag)
{
	// double	npos_x;
	// double	npos_y;

	// npos_x = game->player.x + game->plane_x * game->movespeed * flag;
	// npos_y = game->player.y + game->plane_y * game->movespeed * flag;
	// if (game->map[(int)npos_y][(int)npos_y] == '1')
	// 	return ;
	// game->player.x = npos_x;
	// game->player.y = npos_y;

	double	move_x;
	double	move_y;

	move_x = game->player.x + game->plane_x * game->movespeed * flag;
	move_y = game->player.y + game->plane_y * game->movespeed * flag;
	if (game->map[(int)move_y][(int)move_x] == '1')
		return ;
	game->player.x = move_x;
	game->player.y = move_y;
}

void	key_lr(t_game *game, int flag)
{
	// double	old_dir_x;
	// double	old_plane_x;

	// old_dir_x = game->player.dir_x;
	// old_plane_x = game->plane_x;
	// game->player.dir_x = game->player.dir_x * cos(game->rotspeed * flag) \
	// 					- game->player.dir_y * sin(game->rotspeed * flag);
	// game->player.dir_y = old_dir_x * sin(game->rotspeed * flag) \
	// 					+ game->player.dir_y * cos(game->rotspeed * flag);
	// game->plane_x = game->plane_x * cos(game->rotspeed * flag) \
	// 					- game->plane_y * sin(game->rotspeed * flag);
	// game->plane_y = old_plane_x * sin(game->rotspeed * flag) \
	// 					+ game->plane_y + cos(game->rotspeed * flag);


	double	cp_dir_x;
	double	cp_plane_x;
	double	theta;

	cp_dir_x = game->player.dir_x;
	cp_plane_x = game->plane_x;
	theta = (double)game->rotspeed * flag;
	game->player.dir_x = game->player.dir_x * cos(theta) - game->player.dir_y * sin(theta);
	game->player.dir_y = cp_dir_x * sin(theta) + game->player.dir_y * cos(theta);
	game->plane_x = game->plane_x * cos(theta) - game->plane_y * sin(theta);
	game->plane_y = cp_plane_x * sin(theta) + game->plane_y * cos(theta);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_W)
		key_ws(game, 1);
	else if (key == KEY_S)
		key_ws(game, -1);
	else if (key == KEY_A)
		key_ad(game, -1);
	else if (key == KEY_D)
		key_ad(game, 1);
	else if (key == KEY_LEFT)
		key_lr(game, -1);
	else if (key == KEY_RIGHT)
		key_lr(game, 1);
	else if (key == KEY_ESC)
		exit(0);
	main_loop(game);
	return (0);
}
