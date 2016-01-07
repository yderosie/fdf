/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:25:37 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/16 13:00:07 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

typedef struct	s_line
{
	int l;
	int c;
}				t_line;

typedef struct	s_diff
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
}				t_diff;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	int		y;
	int		x;
	int		z;
	int		**xy;
	double	alt;
	double	alt2;
	int		taille;
	int		d_x;
	int		d_y;
	double	ax;
	double	ay;
	double	az;
	int		first;
	double	cte;
	double	cte2;
	t_line	line;
}				t_env;

typedef struct	s_coordonner
{
	int						y;
	int						x;
	int						z;
	int						first;
	struct s_coordonner		*next;
}				t_coordonner;

int				draw(void *mlx, void *win, int y, int x);
int				key_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);
int				nbline(char *argv);
void			tabint_xy(char **coordonner, int **xy, t_line *l);
void			tabxy(int fd, int ***xy, t_line *l);
int				ft_call(int **xy, t_line *l);
int				color(t_env *e);
t_coordonner	*liste(t_coordonner *point, t_coordonner *maillon);
t_coordonner	*new_maillon(int x, int y, int alt, int first);
void			draw_cas_un(t_diff *d, t_env *e);
void			draw_cas_deux(t_diff *d, t_env *e);
void			draw_cas_trois(t_diff *d, t_env *e);
void			draw_cas_quatre(t_diff *d, t_env *e);
void			verif_cas_un(t_coordonner *c, t_env *e);
void			verif_cas_deux(t_coordonner *c, t_env *e);

#endif
