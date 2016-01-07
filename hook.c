/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 15:30:36 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/18 15:30:37 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int keycode, t_env *e)
{
	if (keycode == 65362)
		e->d_y = e->d_y - 1;
	if (keycode == 65364)
		e->d_y = e->d_y + 1;
	if (keycode == 65361)
		e->d_x = e->d_x - 1;
	if (keycode == 65363)
		e->d_x = e->d_x + 1;
	if (keycode == 112)
		e->cte = (e->cte + 0.2);
	if (keycode == 111)
		e->cte = (e->cte - 0.2);
	if (keycode == 65451)
		e->taille = e->taille + 1;
	if (keycode == 65453)
		e->taille = e->taille - 1;
	expose_hook(&(*e));
	if (keycode == 65307)
		exit (0);
	return (keycode);
}

int		expose_hook(t_env *e)
{
	int				x;
	int				y;
	t_coordonner	*maillon;
	t_coordonner	*list;

	mlx_clear_window(e->mlx, e->win);
	list = NULL;
	y = -1;
	while (++y < e->line.l)
	{
		x = -1;
		while (++x < e->line.c)
		{
			e->alt = e->xy[y][x];
			e->x = ((x + e->d_x) * e->taille) + e->cte * e->alt;
			e->y = ((y + e->d_y) * e->taille) + (e->cte / 2) * e->alt;
			maillon = new_maillon(e->x, e->y, e->alt, 0);
			list = (list == NULL) ? new_maillon(e->x, e->y, e->alt, 1) :
				liste(list, maillon);
		}
	}
	verif_cas_un(list, &(*e));
	verif_cas_deux(list, &(*e));
	return (0);
}

void	verif_cas_un(t_coordonner *c, t_env *e)
{
	t_diff	d;

	while (c->next != NULL)
	{
		d.x1 = c->x;
		d.y1 = c->y;
		d.x2 = c->next->x;
		d.y2 = c->next->y;
		e->alt = c->z;
		if (d.x1 <= d.x2 && (d.x2 - d.x1) >= abs(d.y2 - d.y1))
			draw_cas_un(&d, &(*e));
		if (d.y1 <= d.y2 && (d.y2 - d.y1) >= abs(d.x2 - d.x1))
			draw_cas_trois(&d, &(*e));
		else if ((d.x2 <= d.y1 && (d.y1 - d.y2) >= abs(d.x1 - d.x2)))
			draw_cas_quatre(&d, &(*e));
		c = c->next;
	}
}

void	verif_cas_deux(t_coordonner *c, t_env *e)
{
	t_diff			d;
	t_coordonner	*nbl;
	int				i;

	nbl = c;
	while (c->next != NULL)
	{
		d.x1 = c->x;
		d.y1 = c->y;
		e->alt = c->z;
		i = -1;
		while (++i <= e->line.c && nbl->next != NULL)
		{
			nbl = nbl->next;
			d.x2 = nbl->x;
			d.y2 = nbl->y;
			if (((i == e->line.c) && (!c->first)) || ((i == e->line.c - 1)
					&& (c->first)))
				draw_cas_deux(&d, &(*e));
		}
		nbl = c;
		c = c->next;
	}
}
