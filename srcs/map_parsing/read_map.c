/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doykim <doykim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:52:43 by doykim            #+#    #+#             */
/*   Updated: 2023/01/18 14:08:59 by doykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(char **temp, t_game *game)
{
	int	i;
	int	j;
	int	len;

	i = 6;
	j = 0;
	len = ft_strlen_2d(temp) - 6;
	game->map = (char **)malloc(sizeof(char *) * (len + 1));
	while (temp[i])
		game->map[j++] = ft_strdup(temp[i++]);
	game->map[j] = NULL;
//
	print_2d(game->map);
//
	check_map(game->map);
}

void	check_map(char **map)
{
	int	x;
	int	y;
	int k;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] != '1' && map[x][y] != ' ')
				check_around(map, x, y);
			y++;
		}
		x++;
	}
}

void	check_around(char **map, int x, int y)
{
	int	dx[4] = {-1, 1, 0, 0};
	int	dy[4] = {0, 0, -1, 1};
	int nx;
	int	ny;
	int	k;

	k = 0;
	while (k < 4)
	{
		nx = x + dx[k];
		ny = y + dy[k];
		if (nx > 0 && nx <)
	}
}
