/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complexe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrusu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:26:00 by alrusu            #+#    #+#             */
/*   Updated: 2017/05/16 18:29:32 by alrusu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEXE_H
# define COMPLEXE_H

typedef struct	s_complex
{
	double		a;
	double		b;
}				t_complex;
double			cmagn(t_complex c);
void			cadd(t_complex *c1, t_complex c2);
void			csqr(t_complex *c);
#endif
