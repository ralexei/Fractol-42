# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alrusu <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/16 17:29:30 by alrusu            #+#    #+#              #
#    Updated: 2017/05/16 18:33:44 by alrusu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = main.c tools.c color.c ft_putchar.c ft_putstr.c ft_putendl.c \
	  hooks.c image.c julia.c mandel.c newton.c start_menu.c
OFILES = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OFILES)
	@gcc -Wall -Wextra -Werror -o $@ $^ -lmlx -framework OpenGL \
		-framework AppKit -lm -lpthread -Ofast

%.o: %.c -I.
	@gcc $(FLAGS) -c -o $@ $<

clean:
	@rm -f $(OFILES) color.h.gch keys.h.gch fractol.h.gch complexe.h.gch

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean
