/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperronc <mperronc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 13:47:59 by mperronc          #+#    #+#             */
/*   Updated: 2017/07/31 07:32:46 by tfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

char			*init_color_arena(t_argv *all)
{
	int				i;
	unsigned int	j;
	char			*color;

	color = ft_strnew(MEM_SIZE);
	i = 0;
	while (i < all->n_champs)
	{
		j = 0;
		while (j < all->champ[i].prog_size)
		{
			color[j + ((MEM_SIZE / all->n_champs) * i)] = i + 1;
			j++;
		}
		i++;
	}
	return (color);
}

void			handle_wait(t_argv *info, t_plst *head)
{
	static int	wait = 0;
	int			ch;

	refresh_display(info, head);
	while (wait == 0)
	{
		ch = getch();
		if (ch == '1')
			wait++;
		else if (ch == '2')
			wait += 10;
		else if (ch == '3')
			wait += 100;
		else if (ch == '4')
			wait += 1000;
	}
	wait ? wait-- : wait;
}

void			displaydump(t_argv *info)
{
	if (is_there_flag(info->f, _S_) != -1 && info->f.n != 0
			&& info->cycle % info->f.n == 0)
		dump(info->arena);
	else if (is_there_flag(info->f, _D_) != -1 &&
			info->cycle == (unsigned int)info->f.n)
		dump(info->arena);
}
