/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:56:55 by ayaman            #+#    #+#             */
/*   Updated: 2023/09/11 17:49:10 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



void	init_dda(t_game *game, t_calc *calc)
{
	if (calc->raydirx < 0)
	{
		//printf("game->sidedistx = %f\n", calc->deltadistx);
		calc->stepx = -1;
		calc->sidedistx = (game->ray.posx - calc->mapx) * calc->deltadistx;
		//printf("calc->mapx = %d\n", calc->mapx);
		//printf("game->sidedistx1 = %f\n", calc->sidedistx);
		//calc->sidedistx = (sqrt(1 + (calc->raydiry * calc->raydiry) / (calc->raydirx * calc->raydirx)) * (game->ray.posx - calc->mapx));
		//printf("game->sidedistx = %f\n", calc->sidedistx);
		//printf("calc->deltadistx = %f\n", calc->deltadistx);
	}
	else
	{
		calc->stepx = 1;
		calc->sidedistx = (calc->mapx + 1.0 - game->ray.posx) * calc->deltadistx;
	}
	if (calc->raydiry < 0)
	{
		calc->stepy = -1;
		calc->sidedisty = (game->ray.posy - calc->mapy) * calc->deltadisty;
	}
	else
	{
		calc->stepy = 1;
		calc->sidedisty = \
		(calc->mapy + 1.0 - game->ray.posy) * calc->deltadisty;
	}
}

void	perform_dda(t_game *game, t_calc *calc)
{
	while (calc->hit == 0)
	{
		if (calc->sidedistx < calc->sidedisty)
		{
			calc->sidedistx += calc->deltadistx;
			calc->mapx += calc->stepx;
			//printf("mapx %d\n\r", calc->mapx);
			//printf("stepx %d\r", calc->stepx);
			calc->side = 0;
		}
		else
		{
			calc->sidedisty += calc->deltadisty;
			calc->mapy += calc->stepy;
			//printf("mapy %d\n\r", calc->mapy);
			//printf("stepy %d\n", calc->stepy);
			calc->side = 1;
		}
		if (game->map[calc->mapx][calc->mapy] == '1')
			calc->hit = 1;
	}
	//printf("perwall %f\n", calc->perpwalldist);
	//printf("stepx %f\n", calc->raydirx);

	
 	if (calc->side == 0)
		calc->perpwalldist = (calc->mapx - game->ray.posx + (1 - calc->stepx) / 2) / calc->raydirx;
	else
		calc->perpwalldist = (calc->mapy - game->ray.posy + (1 - calc->stepy) / 2) / calc->raydiry;

}

void	start_ray(int x, t_game *game, t_calc *calc)
{
	calc->camerax = (2 * x / (double)SCREEN_W) - 1; // bu satır bizim hangi pixel sutünunda olduğumuzu belirtir.
	calc->raydirx = game->ray.dirx + game->ray.planex * calc->camerax; // Bu satır da bize x ışınımızın yönünü belirtir
	calc->raydiry = game->ray.diry + game->ray.planey * calc->camerax; // Bu satır da bize y ışınımızın yönünü belirtir
	//printf("raydirx = %f, raydiry = %f\r", calc->raydirx, calc->raydiry);
	calc->mapx = (int)game->ray.posx; // playerin x değeri
	//printf("ray.planey %f \r", game->ray.planey);
	calc->mapy = (int)game->ray.posy; // playerin y değeri
	calc->deltadistx = \
	sqrt(1 + (calc->raydiry * calc->raydiry) / (calc->raydirx * calc->raydirx));
	calc->deltadisty = \
	sqrt(1 + (calc->raydirx * calc->raydirx) / (calc->raydiry * calc->raydiry));
	calc->hit = 0;
}
