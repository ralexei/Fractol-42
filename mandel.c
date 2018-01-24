/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:21:47 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:26:53 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		calc_mand_pixel(t_fractol *f, int x, int y)
{
	int			i;
	t_complex	z;
	t_complex	c;
	double		mu;

	i = 0;
	z.a = 0;
	z.b = 0;
	c.a = (double)(x - (WIN_WID / 2)) / ((double)WIN_WID / 4 * f->zoom) + f->x;
	c.b = (double)(y - (WIN_HGT / 2)) / ((double)WIN_HGT / 4 * f->zoom) + f->y;
	while (i < f->itterations && cmagn(z) < 4)
	{
		i++;
		csqr(&z);
		cadd(&z, c);
	}
	csqr(&z);
	cadd(&z, c);
	csqr(&z);
	cadd(&z, c);
	i += 2;
	mu = i + 1 - log((log(cmagn(z)) / 2.0f) / log(2)) / log(2);
	return ((i < f->itterations) ? get_color(mu, f) : 0x000000);
}

static void		*draw_mand(void *p)
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
			pixel_put(&t->f, x, y, calc_mand_pixel(&(t->f), x, y));
			y++;
		}
		x++;
	}
	return (NULL);
}

void			mandelbrot(t_fractol *f)
{
	pthread_t	threads[4];
	t_thread	t[4];
	int			i;

	i = 0;
	t[0].f = *f;
	t[0].l = (t_limit){0, WIN_WID / 2, 0, WIN_HGT / 2};
	pthread_create(&threads[0], NULL, draw_mand, (void *)&t[0]);
	t[1].f = *f;
	t[1].l = (t_limit){WIN_WID / 2, WIN_WID, 0, WIN_HGT / 2};
	pthread_create(&threads[1], NULL, draw_mand, (void *)&t[1]);
	t[2].f = *f;
	t[2].l = (t_limit){0, WIN_WID / 2, WIN_HGT / 2, WIN_HGT};
	pthread_create(&threads[2], NULL, draw_mand, (void *)&t[2]);
	t[3].f = *f;
	t[3].l = (t_limit){WIN_WID / 2, WIN_WID, WIN_HGT / 2, WIN_HGT};
	pthread_create(&threads[3], NULL, draw_mand, (void *)&t[3]);
	while (i < 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
