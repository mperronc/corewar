/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_refreshers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperronc <mperronc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 19:58:50 by mperronc          #+#    #+#             */
/*   Updated: 2017/08/02 00:30:01 by mperronc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

#define P_I proc->instruct
#define PC proc->pc
#define P proc

void		refresh_arena(char *arena, char *color, WINDOW *win)
{
	int	i;

	box(win, 0, 0);
	mvwprintw(win, 0, 2, "ARENA");
	i = 0;
	while (i < MEM_SIZE)
	{
		wattron(win, COLOR_PAIR(color[i]));
		mvwprintw(win, (i / 64) + 1, ((i % 64) * 3) + 1, "%s",
		ft_bytohex(arena[i], TRUE));
		wattroff(win, COLOR_PAIR(color[i]));
		i++;
	}
	wrefresh(win);
}

void		refresh_process(WINDOW *win, WINDOW *arena, t_process *proc)
{
	int i;

	werase(win);
	box(win, 0, 0);
	mvwprintw(win, 0, 2, "CHAMPION %d'S PROCESS", proc->id);
	mvwprintw(win, 1, 1, "CARRY : %d | LIVE : %d | PC : %d | WAIT : %d",
	proc->carry, proc->exec_live, proc->pc, proc->wait);
	i = 0;
	while (i < 4)
	{
		mvwprintw(win, 2 + i, 1, "%10d %10d %10d %10d", proc->reg[(i * 4)],
		proc->reg[(i * 4) + 1], proc->reg[(i * 4) + 2], proc->reg[(i * 4) + 3]);
		i++;
	}
	if (proc->instruct)
	{
		mvwprintw(win, 6, 1, "CURRENT OP : %s", op(proc->instruct->opcode));
		mvwprintw(win, 7, 1, "TYPES : %10s %10s %10s",
		types(P_I->types[0]), types(P_I->types[1]), types(P_I->types[2]));
		mvwprintw(win, 8, 1, "ARGS :  %10d %10d %10d", proc->instruct->args[0],
		proc->instruct->args[1], proc->instruct->args[2]);
	}
	mvwchgat(arena, PC / 64 + 1, (PC % 64) * 3 + 1, 2, A_REVERSE, P->id, NULL);
	wrefresh(win);
	wrefresh(arena);
}

void		refresh_info(t_argv *all, WINDOW *win)
{
	werase(win);
	box(win, 0, 0);
	mvwprintw(win, 0, 2, "VM STATUS");
	mvwprintw(win, 1, 35, "GUI MODE : %s", all->gui->mode == 1 ?
									"STEP MODE" : "INSTANT MODE");
	mvwprintw(win, 1, 1, "CYCLE : %d", all->cycle);
	mvwprintw(win, 2, 1, "CYCLE TO DIE : %d", all->cycle_to_die);
	mvwprintw(win, 3, 1, "CYCLE DELTA : %d", CYCLE_DELTA);
	mvwprintw(win, 4, 1, "CHECKS : %d", all->checks);
	mvwprintw(win, 5, 1, "MAX CHECKS : %d", MAX_CHECKS);
	mvwprintw(win, 6, 1, "LAST LIVING PLAYER : %d", *last_living_player());
	mvwprintw(win, 8, 1, "Controls :");
	mvwprintw(win, 9, 1, "S to step forward one cycle.");
	mvwprintw(win, 10, 1, "D to toggle debug view");
	mvwprintw(win, 11, 1, "1-9 to skip forward 1, 10, 100 ... cycles");
	mvwprintw(win, 12, 1, "M to toggle between step mode or instant mode");
	mvwprintw(win, 14, 1, "by tfontain, jgagnot and mperronc @ 42 - 2017");
	wrefresh(win);
}

void		refresh_champion(t_header *champ, WINDOW *win, int i)
{
	box(win, 0, 0);
	mvwprintw(win, 0, 2, "CHAMPION %d", i);
	mvwprintw(win, 1, 1, "%.130s", champ->prog_name);
	mvwprintw(win, 2, 1, "%.130s", champ->comment);
	wrefresh(win);
}

void		refresh_display(t_argv *all, t_plst *head)
{
	int i;

	refresh_arena(all->arena, all->color, all->gui->win_arena);
	refresh_info(all, all->gui->win_vm_info);
	i = 0;
	while (i < all->n_champs)
	{
		refresh_champion(&(all->champ[i]), all->gui->win_champions[i], i + 1);
		i++;
	}
	if (all->gui->debug == 1)
		refresh_wlist(head, all);
}
