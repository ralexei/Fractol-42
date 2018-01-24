/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:53:42 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:29:43 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define Z	0
#define T	1
#define D	2
#define MX	0
#define MY	1
#define N	0
#define MIN	1e-6
#define MAX	1e+6

static int		prepare_newton_pixel(t_fractol *f, int x, int y)
{
	t_complex	z;
	t_complex	old;
	int			i;
	double		tmp;

	z.a = (x - WIN_WID / 2) / (0.25 * f->zoom * WIN_WID) + f->x;
	z.b = (y - WIN_HGT / 2) / (0.25 * f->zoom * WIN_HGT) + f->y;
	i = 0;
	tmp = 1.0;
	while (tmp > 0.000001 && ++i < f->itterations)
	{
		old = z;
		tmp = (z.a * z.a + z.b * z.b) * (z.a * z.a + z.b * z.b);
		z.a = (2 * z.a * tmp + z.a * z.a - z.b * z.b) / (3.0 * tmp);
		z.b = (2 * z.b * (tmp - old.a)) / (3.0 * tmp);
		tmp = (z.a - old.a) * (z.a - old.a) + (z.b - old.b) * (z.b - old.b);
	}
	return ((((i * 9) % 255) << 16) + (0 << 8) + ((i * 9) % 255));
}

static void		*newton_thread(void *p)
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
			pixel_put(&t->f, x, y, prepare_newton_pixel(&(t->f), x, y));
			y++;
		}
		x++;
	}
	return (NULL);
}

void			newton(t_fractol *f)
{
	pthread_t	threads[4];
	t_thread	t[4];
	int			i;

	t[0].f = *f;
	t[0].l = (t_limit){0, WIN_WID / 2, 0, WIN_HGT / 2};
	pthread_create(&threads[0], NULL, newton_thread, (void *)&t[0]);
	t[1].f = *f;
	t[1].l = (t_limit){WIN_WID / 2, WIN_WID, 0, WIN_HGT / 2};
	pthread_create(&threads[1], NULL, newton_thread, (void *)&t[1]);
	t[2].f = *f;
	t[2].l = (t_limit){0, WIN_WID / 2, WIN_HGT / 2, WIN_HGT};
	pthread_create(&threads[2], NULL, newton_thread, (void *)&t[2]);
	t[3].f = *f;
	t[3].l = (t_limit){WIN_WID / 2, WIN_WID, WIN_HGT / 2, WIN_HGT};
	pthread_create(&threads[3], NULL, newton_thread, (void *)&t[3]);
	i = 0;
	while (i < 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
