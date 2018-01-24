/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:27:48 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:30:43 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_WID			500
# define WIN_HGT			500
# define TRANSLATE_DIST		0.1
# define SCROLL_LIMIT		7
# define ZOOM				0.7
# define USAGE_ERROR		"usage: ./fractol [mandelbrot|julia|newton]"
# define MOTION_NOTIFY		6
# define PTR_MOTION_MASK	(1L << 6)
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdlib.h>
# include "complexe.h"
# include "color.h"
# include "keys.h"

typedef struct	s_limit
{
	int			minx;
	int			maxx;
	int			miny;
	int			maxy;
}				t_limit;

typedef struct	s_img
{
	void		*img;
	char		*str;
	int			endian;
	int			bpp;
	int			sline;
}				t_img;

typedef struct	s_palette
{
	int			count;
	t_color		colors[10];
}				t_palette;

typedef struct	s_fractol
{
	int			jul;
	int			mousex;
	int			mousey;
	int			hooking;
	int			can_draw;
	int			itterations;
	int			scroll_count;
	int			selected_palette;
	void		*mlx;
	void		*win;
	double		zoom;
	double		x;
	double		y;
	double		cre;
	double		cim;
	t_img		img;
	t_palette	palette[5];
	void		(*draw)(struct s_fractol *);
}				t_fractol;

typedef struct	s_thread
{
	t_fractol	f;
	t_limit		l;
	int			id;
}				t_thread;
void			pixel_put(t_fractol *f, int x, int y, int color);
void			julia(t_fractol *f);
void			mandelbrot(t_fractol *f);
int				get_color(double mu, t_fractol *f);
double			log2(double x);
int				ft_lerpi(int first, int second, double p);
int				input(int key, t_fractol *f);
int				expose_hook(t_fractol *f);
int				mouse_hook(int key, int x, int y, t_fractol *f);
int				loop_hook(t_fractol *f);
void			newton(t_fractol *f);
int				julia_mouse(int x, int y, t_fractol *f);
int				ft_strcmp(const char *s1, const char *s2);
char			*str_to_lower(char *str);
double			sqr(double nr);
void			ft_putendl(const char *s);
void			ft_putstr(const char *s);
void			init_palettes(t_fractol *f);
void			rand_palette(t_fractol *f);
void			ft_putchar(char c);
void			start_menu(t_fractol *f);
#endif
