/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 18:28:39 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/06 05:39:37 by yderosie         ###   ########.fr       */
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
	if (keycode == 65451)
	{
		e->taille = e->taille + 1;
		expose_hook(&(*e));
	}
	if (keycode == 65453)
	{
		e->taille = e->taille - 1;
		expose_hook(&(*e));
	}
	if (keycode == 65307)
		exit (0);
	return (0);
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
			e->x = (x * e->taille) + CTE * e->xy[y][x];
			if ((e->xy[y][x] > 0) || ((e->xy[y][x + 1] > 0) && e->xy[y + 1][x] > 0))
				e->alt = 1;
			else if (e->xy[y][x] < 0)
				e->alt = -1;
			else
				e->alt = 0;
			e->y = (y * e->taille) + (CTE / 2) * e->xy[y][x];
			maillon = new_maillon(e->x, e->y, e->alt);
			if (list == NULL)
				list = new_maillon(e->x, e->y, e->alt);
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

void	draw_cas_un(float x1, float y1, float x2, float y2, t_env *e)
{
	float x;

	x = x1;
	while (x <= x2)
	{
		if (e->alt > 0)
			mlx_pixel_put(e->mlx, e->win, x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1),
				0xFFFFFF);
		else if (e->alt < 0)
			mlx_pixel_put(e->mlx, e->win, x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1),
				0x0000FF);
		else
			mlx_pixel_put(e->mlx, e->win, x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1),
				0xAA0000);
		x++;
	}
}

void	draw_cas_deux(float x1, float y1, float x2, float y2, t_env *e)
{
	float y;

	y = y2;
	while (y <= y1)
	{
		if (e->alt > 0)
			mlx_pixel_put(e->mlx, e->win, x1 + ((x2 - x1) * (y - y1)) / (y2 - y1), y,
				0xFFFFFF);
		else if (e->alt > 0)
			mlx_pixel_put(e->mlx, e->win, x1 + ((x2 - x1) * (y - y1)) / (y2 - y1), y,
				0x0000FF);
		else
			mlx_pixel_put(e->mlx, e->win, x1 + ((x2 - x1) * (y - y1)) / (y2 - y1), y,
				0xAA0000);
		y++;
	}
}

void	verif_cas_un(t_coordonner *c, t_env *e)
{
	float		x1;
	float		y1;
	float		x2;
	float		y2;

	while (c->next != NULL)
	{
		x1 = c->x;
		y1 = c->y;
		x2 = c->next->x;
		y2 = c->next->y;
		e->alt = c->alt;
		if (x1 <= x2 && (x2 - x1) >= abs(y2 - y1))
			draw_cas_un(x1, y1, x2, y2, &(*e));
		c = c->next;
	}
}

void	verif_cas_deux(t_coordonner *c, t_env *e)
{
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	t_coordonner *nbl;
	int i;

	nbl = c;
	while (c->next != NULL)
	{
		x1 = c->x;
		y1 = c->y;
		e->alt = c->alt;
		i = 0;
		while (i <= e->line.c && nbl->next != NULL)
		{
			nbl = nbl->next;
			x2 = nbl->x;
			y2 = nbl->y;
/*			if (x1 <= x2 && (x2 - x1) >= abs(y2 - y1))
				draw_cas_un(x1, y1, x2, y2, &(*e));
*/			if (((i == e->line.c) && (y1 <= y2 && (y2 - y1) >= abs(x2 - x1)) && (x1 				!= 0 && x2 != 0)) || (x1 == 0 && x2 == 0))
				draw_cas_deux(x2, y2, x1, y1, &(*e));
			i++;
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

t_coordonner	*new_maillon(int x, int y, int alt)
{
	t_coordonner	*point;

	point = (t_coordonner *)malloc(sizeof(t_coordonner));
	if (point == NULL)
		return (NULL);
	point->x = x;
	point->y = y;
	point->alt = alt;
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
	e.win = mlx_new_window(e.mlx, 840, 840, "42");
	e.xy = xy;
	e.line = (*l);
	e.taille = 10;
	mlx_key_hook(e.win, key_hook, &e);
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
