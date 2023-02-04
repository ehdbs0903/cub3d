/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:43:27 by doykim            #+#    #+#             */
/*   Updated: 2023/02/04 16:52:23 by sanghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	main_loop(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->ceil, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->floor, 0, 540);
//	set_background(game);
	raycasting(game);
//	paint_img(game);
//	key_hook(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
}

