/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 18:28:39 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/16 17:10:11 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

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

int color(t_env *e)
{
	return ((RGB(127.5 * (cos(e->alt) + 1),
	127.5 * (sin(e->alt) + 1),
	127.5 * (1 - cos(e->alt)))));
}

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

t_coordonner	*liste(t_coordonner *point, t_coordonner *maillon)
{
	t_coordonner *first;

	first = point;
	while (first->next != NULL)
		first = first->next;
	first->next = maillon;
	return (point);
}

t_coordonner	*new_maillon(int x, int y, int alt, int first)
{
	t_coordonner	*point;

	point = (t_coordonner *)malloc(sizeof(t_coordonner));
	if (point == NULL)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = alt;
	point->first = first;
	point->next = NULL;
	return (point);
}

int		ft_call(int **xy, t_line *l)
{
	t_env			e;

	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 840, 840, "42");
	e.xy = xy;
	e.line = (*l);
	e.taille = 10;
	e.cte = -0.5;
	e.d_x = 0;
	e.d_y = 0;
	e.ax = 0;
	e.ay = 0;
	e.alt2 = 0;
	e.az = 0;
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

int		nbline(char *argv)
{
	char	*s;
	int		fd;
	int		j;

	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &s))
		j++;
	free(s);
	close(fd);
	return (j);
}

void		tabint_xy(char **coordonner, int **xy, t_line *l)
{
	int		j;

	j = 0;
	while (coordonner[j] != '\0')
		j++;
	(*xy) = (int *)malloc(sizeof(int) * (j + 1));
	j = 0;
	while (coordonner[j] != '\0')
	{
		(*xy)[j] = ft_atoi(coordonner[j]);
		j++;
	}
	if (j > l->c)
		l->c = j;
}

void	tabxy(int fd, int ***xy, t_line *l)
{
	char		*line;
	char		**coordonner;
	int			j;

	while (get_next_line(fd, &line))
	{
		coordonner = ft_strsplit(line, ' ');
		tabint_xy(coordonner, &(*xy)[j], &(*l));
		j++;
	}
	l->l = j;
}

int		main(int argc, char **argv)
{
	int		fd;
	int		**xy;
	t_line	l;

	if (argc == 2)
	{
		l.l = 0;
		l.c = 0;
		xy = (int **)malloc(sizeof(int *) * (nbline(argv[1]) + 2));
		fd = open(argv[1], O_RDONLY);
		tabxy(fd, &xy, &l);
	}
	ft_call(xy, &l);
	return (0);
}
