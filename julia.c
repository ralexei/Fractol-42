/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:51:55 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:32:30 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				julia_mouse(int x, int y, t_fractol *f)
{
	if (f->jul)
	{
		f->cre = (double)x / (double)WIN_WID * 4 - 5.9;
		f->cim = (double)y / (double)WIN_HGT * 4 - 2.1;
		expose_hook(f);
	}
	return (0);
}

static void		process_error(t_complex *znew, t_complex c)
{
	csqr(znew);
	cadd(znew, c);
	csqr(znew);
	cadd(znew, c);
}

static int		color_julia_pixel(t_fractol *f, int x, int y)
{
	int			i;
	t_complex	c;
	t_complex	znew;
	t_complex	zold;
	double		mu;

	i = 0;
	c.a = f->cre;
	c.b = f->cim;
	znew.a = (double)(x - (WIN_WID / 2)) / ((double)WIN_WID / 4 * f->zoom)
		+ f->x;
	znew.b = (double)(y - (WIN_HGT / 2)) / ((double)WIN_HGT / 4 * f->zoom)
		+ f->y;
	mu = exp(-cmagn(znew));
	while (i < f->itterations && cmagn(znew) < 4)
	{
		zold = znew;
		csqr(&znew);
		cadd(&znew, c);
		mu += exp(-cmagn(znew));
		i++;
	}
	process_error(&znew, c);
	i += 2;
	return ((i < f->itterations) ? get_color(mu, f) : 0x000000);
}

static void		*julia_thread(void *p)
{
	t_thread	*t;
	int			x;
	int			y;

	t = (t_thread *)p;
	x = t->l.minx;
	while (x < t->l.maxx)
	{
		y = t->l.miny;
		while (y < t->l.maxy)
		{
			pixel_put(&t->f, x, y, color_julia_pixel(&(t->f), x, y));
			y++;
		}
		x++;
	}
	return (NULL);
}

void			julia(t_fractol *f)
{
	pthread_t	threads[4];
	t_thread	t[4];
	int			i;

	i = 0;
	t[0].f = *f;
	t[0].l = (t_limit){0, WIN_WID / 2, 0, WIN_HGT / 2};
	pthread_create(&threads[0], NULL, julia_thread, (void *)&t[0]);
	t[1].f = *f;
	t[1].l = (t_limit){WIN_WID / 2, WIN_WID, 0, WIN_HGT / 2};
	pthread_create(&threads[1], NULL, julia_thread, (void *)&t[1]);
	t[2].f = *f;
	t[2].l = (t_limit){0, WIN_WID / 2, WIN_HGT / 2, WIN_HGT};
	pthread_create(&threads[2], NULL, julia_thread, (void *)&t[2]);
	t[3].f = *f;
	t[3].l = (t_limit){WIN_WID / 2, WIN_WID, WIN_HGT / 2, WIN_HGT};
	pthread_create(&threads[3], NULL, julia_thread, (void *)&t[3]);
	while (i < 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
