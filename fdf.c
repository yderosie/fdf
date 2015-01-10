/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 18:28:39 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/10 01:18:06 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

int		draw(void *mlx, void *win, int y, int x)
{
//	int	k;
//	int i;
//	int	j;
//
/*	y = y * 40;
	x = x * 40;*/
	mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
	return (0);
}


int		key_hook(int keycode, t_env *e)
{
	if (keycode == 65362)
		e->decallage_y = e->decallage_y - 1;
	if (keycode == 65364)
		e->decallage_y = e->decallage_y + 1;
	if (keycode == 65361)
		e->decallage_x = e->decallage_x - 1;
	if (keycode == 65363)
		e->decallage_x = e->decallage_x + 1;
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
	int		x;
	int		y;
	t_coordonner	*maillon;
	t_coordonner	*list;

	mlx_clear_window(e->mlx, e->win);
	list = NULL;
	y = 0;
	while (y < e->line.l)
	{
		x = 0;
		while (x < e->line.c)
		{
			e->x = ((x + e->decallage_x) * e->taille) + e->cte * e->xy[y][x];
			e->alt = e->xy[y][x];
			e->y = ((y + e->decallage_y) * e->taille) + (e->cte / 2) * e->xy[y][x];
			maillon = new_maillon(e->x, e->y, e->alt, 0);
			if (list == NULL)
				list = new_maillon(e->x, e->y, e->alt, 1);
			else
				list = liste(list, maillon);
			x++;
		}
		y++;
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

void	draw_cas_un(float x1, float y1, float x2, float y2, t_env *e)
{
	float x;

	x = x1;
	while (x <= x2)
	{
			mlx_pixel_put(e->mlx, e->win, x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1)				,color(&(*e)));
		x++;
	}
}

void	draw_cas_deux(float x1, float y1, float x2, float y2, t_env *e)
{
	float y;

	y = y2;
	while (y <= y1)
	{
			mlx_pixel_put(e->mlx, e->win, x1 + ((x2 - x1) * (y - y1)) / (y2 - y1), y				,color(&(*e)));
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
		e->alt = c->alt;
//		if (d.x1 <= d.x2 && (d.x2 - d.x1) >= abs(d.y2 - d.y1))
			draw_cas_un(d.x1, d.y1, d.x2, d.y2, &(*e));
		c = c->next;
	}
}

void	verif_cas_deux(t_coordonner *c, t_env *e)
{
	t_diff			d;
	t_coordonner	*nbl;
	int i;

	nbl = c;
	while (c->next != NULL)
	{
		d.x1 = c->x;
		d.y1 = c->y;
		e->alt = c->alt;
		i = -1;
		while (++i <= e->line.c && nbl->next != NULL)
		{
			nbl = nbl->next;
			d.x2 = nbl->x;
			d.y2 = nbl->y;
			if (((i == e->line.c) && (/*(d.y1 <= d.y2 && (d.y2 - d.y1) >=
				abs(d.x2 - d.x1)) && */(!c->first))) || ((i == e->line.c - 1) && (c->first)))
				draw_cas_deux(d.x2, d.y2, d.x1, d.y1, &(*e));
			//i++;
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
	point->alt = alt;
	point->first = first;
	point->next = NULL;
	return (point);
}

int		ft_call(int **xy, t_line *l)
{
	t_env			e;
//	int				y;
//	int				x;

//	list = NULL;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 1400, 1400, "42");
	e.xy = xy;
	e.line = (*l);
	e.taille = 10;
	e.cte = -2;
	e.cte2 = -0.8;
	e.decallage_x = 0;
	e.decallage_y = 0;
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
//	mlx_hook(e.win, KeyPress, KeyPressMask, keypress_hook, &e);
//	mlx_hook(e.win, KeyRelease, KeyReleaseMask, keyrelease_hook, &e);
/*	y = 0;
	while (y < l->l)
	{
		x = 0;
		while (x < l->c)
		{
			e.x = (x * 10) + cte * xy[y][x];
			e.y = (y * 10) + (cte / 2) * xy[y][x];
			draw(e.mlx, e.win, e.y, e.x);
			maillon = new_maillon(e.x, e.y);
			if (list == NULL)
				list = new_maillon(e.x, e.y);
			else
				list = liste(list, maillon);
			x++;
		}
		y++;
	}
	verif_cas_un(list, &e);
	verif_cas_deux(list, &e, &(*l));*/
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
	int fd;
	int j;
	int **xy;
	int c;
	t_line l;

	if (argc == 2)
	{
		l.l = 0;
		l.c = 0;
		xy = (int **)malloc(sizeof(int *) * (nbline(argv[1]) + 2));
		fd = open(argv[1], O_RDONLY);
		tabxy(fd, &xy, &l);
		printf("%d\n%d\n", l.l, l.c);
		c = 0;
		j = 0;
		while (j < l.l)
		{
			c = 0;
			while (c < l.c)
			{
				printf("%d ", xy[j][c]);
				c++;
			}
			printf("\n");
			j++;
		}
	}
	ft_call(xy, &l);
	return (0);
}
