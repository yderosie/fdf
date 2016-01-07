/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 18:28:39 by yderosie          #+#    #+#             */
/*   Updated: 2015/03/18 14:36:23 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				color(t_env *e)
{
	return ((RGB(127.5 * (cos(e->alt) + 1),
	127.5 * (sin(e->alt) + 1),
	127.5 * (1 - cos(e->alt)))));
}

int				ft_call(int **xy, t_line *l)
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

int				main(int argc, char **argv)
{
	int		fd;
	int		**xy;
	t_line	l;

	if (argc == 2)
	{
		l.l = 0;
		l.c = 0;
		xy = (int **)malloc(sizeof(int *) * (nbline(argv[1]) + 2));
		if (xy == NULL)
			return (0);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (-1);
		tabxy(fd, &xy, &l);
		close(fd);
		ft_call(xy, &l);
	}
	return (0);
}
