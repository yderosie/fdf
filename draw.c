/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 15:30:21 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/18 15:30:23 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_cas_un(t_diff *d, t_env *e)
{
	double x;
	double x1;
	double x2;
	double y1;
	double y2;

	x1 = d->x1;
	x2 = d->x2;
	y1 = d->y1;
	y2 = d->y2;
	x = x1;
	while (x <= x2)
	{
		mlx_pixel_put(e->mlx, e->win, x, y1 + ((y2 - y1) * (x - x1)) /
			(x2 - x1), color(&(*e)));
		x++;
	}
}

void	draw_cas_deux(t_diff *d, t_env *e)
{
	double y;
	double x1;
	double x2;
	double y1;
	double y2;

	x1 = d->x2;
	x2 = d->x1;
	y1 = d->y2;
	y2 = d->y1;
	y = y2;
	while (y <= y1)
	{
		mlx_pixel_put(e->mlx, e->win, x1 + ((x2 - x1) * (y - y1)) /
			(y2 - y1), y, color(&(*e)));
		y++;
	}
}

void	draw_cas_trois(t_diff *d, t_env *e)
{
	double x;
	double x1;
	double x2;
	double y1;
	double y2;

	x1 = d->x1;
	x2 = d->x2;
	y1 = d->y1;
	y2 = d->y2;
	x = y1;
	while (x <= y2)
	{
		mlx_pixel_put(e->mlx, e->win, x1 + ((x2 - x1) * (x - y1)) / (y2 - y1)
			, x, color(&(*e)));
		x++;
	}
}

void	draw_cas_quatre(t_diff *d, t_env *e)
{
	double y;
	double x1;
	double x2;
	double y1;
	double y2;

	x1 = d->x1;
	x2 = d->x2;
	y1 = d->y1;
	y2 = d->y2;
	y = y2;
	while (y <= y1)
	{
		mlx_pixel_put(e->mlx, e->win, x1 + ((x2 - x1) * (y - y1)) /
			(y2 - y1), y, color(&(*e)));
		y++;
	}
}
