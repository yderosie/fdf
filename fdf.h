/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:25:37 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/09 04:32:34 by yderosie         ###   ########.fr       */
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
	float	x1;
	float	x2;
	float	y1;
	float	y2;
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
	int		taille;
	int		decallage_x;
	int		decallage_y;
	float	cte;
	float	cte2;
	t_line	line;
}				t_env;

typedef struct	s_coordonner
{
	int						y;
	int						x;
	int						alt;
	int						first;
	struct s_coordonner		*next;
}				t_coordonner;

int				draw(void *mlx, void *win, int y, int x);
int				key_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);
int				call(int y, int x);
t_coordonner	*liste(t_coordonner *point, t_coordonner *maillon);
t_coordonner	*new_maillon(int x, int y, int alt, int first);
void			verif_cas_un(t_coordonner *c, t_env *e);
void			verif_cas_deux(t_coordonner *c, t_env *e);

#endif
