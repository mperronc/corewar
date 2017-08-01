/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperronc <mperronc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 13:47:59 by mperronc          #+#    #+#             */
/*   Updated: 2017/08/02 00:29:59 by mperronc         ###   ########.fr       */
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

static void		toggle_debug(t_argv *info, t_plst *head)
{
	info->gui->debug = -(info->gui->debug);
	if (info->gui->debug == 1)
		refresh_wlist(head, info);
	else
		erase_wlist(info->gui->wlist_process);
}

void			handle_wait(t_argv *info, t_plst *head)
{
	static int	wait = 0;
	int			ch;

	if (wait == 0 || info->gui->mode == STEP)
		refresh_display(info, head);
	while (wait == 0)
	{
		ch = getch();
		if (ch >= '1' && ch <= '5')
			wait += ft_pow(10, ch - '0' - 1);
		else if (ch == 's')
			wait += 1;
		else if (ch == 'd')
			toggle_debug(info, head);
		else if (ch == 'm')
		{
			info->gui->mode = -(info->gui->mode);
			refresh_info(info, info->gui->win_vm_info);
		}
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
