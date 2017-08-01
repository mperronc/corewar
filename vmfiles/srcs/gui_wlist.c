/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_wlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperronc <mperronc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:01:53 by mperronc          #+#    #+#             */
/*   Updated: 2017/08/02 00:30:01 by mperronc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

#define Y ((n % WPH) * PH)
#define X (AW + ((n / WPH) * PW))

WINDOW	**build_wlist(void)
{
	WINDOW		**wlist;
	int			n;

	wlist = (WINDOW **)malloc(sizeof(WINDOW *) * DEBUG_MAX_PROC);
	n = 0;
	while (n < DEBUG_MAX_PROC)
	{
		wlist[n] = newwin(PH, PW, Y, X);
		n++;
	}
	return (wlist);
}

void	erase_wlist(WINDOW **wlist)
{
	int n;

	n = 0;
	while (n < DEBUG_MAX_PROC)
	{
		werase(wlist[n]);
		wrefresh(wlist[n]);
		n++;
	}
}

void	refresh_wlist(t_plst *plst, t_argv *all)
{
	WINDOW	**wlist;
	int		n;

	n = 0;
	wlist = all->gui->wlist_process;
	while (plst && n < DEBUG_MAX_PROC)
	{
		refresh_process(wlist[n], all->gui->win_arena, &plst->proc);
		n++;
		plst = plst->nxt;
	}
	while (n < DEBUG_MAX_PROC)
	{
		werase(wlist[n]);
		wrefresh(wlist[n]);
		n++;
	}
}
