/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:25:37 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/06 05:37:53 by yderosie         ###   ########.fr       */
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

# define CTE -2
# define CTE2 1

typedef struct	s_line
{
	int l;
	int c;
}				t_line;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	int		y;
	int		x;
	int		z;
	int		**xy;
	int		alt;
	int		taille;
	t_line	line;
}				t_env;

typedef struct	s_coordonner
{
	int						y;
	int						x;
	int						alt;
	struct s_coordonner		*next;
}				t_coordonner;

int				draw(void *mlx, void *win, int y, int x);
int				key_hook(int keycode, t_env *e);
int				expose_hook(t_env *e);
int				call(int y, int x);
t_coordonner	*liste(t_coordonner *point, t_coordonner *maillon);
t_coordonner	*new_maillon(int x, int y, int alt);
void			verif_cas_un(t_coordonner *c, t_env *e);
void			verif_cas_deux(t_coordonner *c, t_env *e);

#endif
