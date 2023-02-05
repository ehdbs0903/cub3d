/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:48:22 by doykim            #+#    #+#             */
/*   Updated: 2023/02/05 16:53:00 by doykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(int ac, char *av[], t_game *game, t_img *img)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(game, 0, sizeof(t_img));
	game->movespeed = 0.01;
	game->rotspeed = 0.01;
	game->mlx = mlx_init();
	check_file(ac, av, game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
}
