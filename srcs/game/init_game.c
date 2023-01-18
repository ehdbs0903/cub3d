/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doykim <doykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:48:22 by doykim            #+#    #+#             */
/*   Updated: 2023/01/18 13:23:34 by doykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->width = 0;
	game->height = 0;
	game->p_cnt = 0;
	game->map = NULL;
}
