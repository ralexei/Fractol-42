/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:29:56 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:29:57 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# define R 0
# define G 1
# define B 2

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;
t_color			clerp(t_color c1, t_color c2, double p);
#endif
