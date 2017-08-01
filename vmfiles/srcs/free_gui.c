/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperronc <mperronc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 18:45:06 by mperronc          #+#    #+#             */
/*   Updated: 2017/08/02 00:29:58 by mperronc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void		free_champs(WINDOW **wins, int n)
{
	int			i;

	i = 0;
	while (i < n)
	{
		delwin(wins[i]);
		i++;
	}
	free(wins);
}

static void		free_wlist(WINDOW **wlist)
{
	int n;

	n = 0;
	while (n < DEBUG_MAX_PROC)
	{
		delwin(wlist[n]);
		n++;
	}
	free(wlist);
}

void			free_gui(t_argv *all)
{
	t_gui		*gui;

	gui = all->gui;
	delwin(gui->win_arena);
	delwin(gui->win_vm_info);
	free_champs(gui->win_champions, all->n_champs);
	free_wlist(gui->wlist_process);
}
