/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontain <tfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:46:49 by tfontain          #+#    #+#             */
/*   Updated: 2017/08/02 00:30:07 by mperronc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static inline int		select_process(t_plst *p_current, t_plst **p_head,
		char *arena, char *color)
{
	if (p_current->proc.instruct->opcode == 0x09)
		op_zjmp(&p_current->proc, arena);
	else if (p_current->proc.instruct->opcode == 0x0A)
		op_ldi(&p_current->proc, p_current->proc.instruct, arena);
	else if (p_current->proc.instruct->opcode == 0x0B)
		op_sti(&p_current->proc, p_current->proc.instruct, arena, color);
	else if (p_current->proc.instruct->opcode == 0x0C)
		op_fork(p_current, p_head, p_current->proc.instruct);
	else if (p_current->proc.instruct->opcode == 0x0D)
		op_lld(&p_current->proc, p_current->proc.instruct, arena);
	else if (p_current->proc.instruct->opcode == 0x0E)
		op_lldi(&p_current->proc, p_current->proc.instruct, arena);
	else if (p_current->proc.instruct->opcode == 0x0F)
		op_lfork(p_current, p_head, p_current->proc.instruct);
	else if (p_current->proc.instruct->opcode == 0x10)
		op_aff(&p_current->proc, p_current->proc.instruct);
	return (0);
}

/*
** func to check the number of call to live
*/

static inline int		select_process_and_execute(t_plst *p_current,
		t_plst **p_head, char *arena, char *color)
{
	if (p_current->proc.instruct->opcode == 0x01)
		op_live(&p_current->proc, p_current->proc.instruct);
	else if (p_current->proc.instruct->opcode == 0x02)
		op_ld(&p_current->proc, p_current->proc.instruct, arena);
	else if (p_current->proc.instruct->opcode == 0x03)
		op_st(&p_current->proc, p_current->proc.instruct, arena, color);
	else if (p_current->proc.instruct->opcode == 0x04)
		op_add(&p_current->proc, p_current->proc.instruct);
	else if (p_current->proc.instruct->opcode == 0x05)
		op_sub(&p_current->proc, p_current->proc.instruct);
	else if (p_current->proc.instruct->opcode == 0x06)
		op_and(&p_current->proc, p_current->proc.instruct, arena);
	else if (p_current->proc.instruct->opcode == 0x07)
		op_or(&p_current->proc, p_current->proc.instruct, arena);
	else if (p_current->proc.instruct->opcode == 0x08)
		op_xor(&p_current->proc, p_current->proc.instruct, arena);
	else
		select_process(p_current, p_head, arena, color);
	return (0);
}

/*
** execute the register onto which there is the current processus
** see processus->pc;
*/

static void				execute_one_process(t_plst *curr, t_plst **head,
		t_argv *info)
{
	if (!curr->proc.instruct)
	{
		if (!(curr->proc.instruct =
			check_operation(info->arena, &curr->proc, info->ref_tab)))
		{
			curr->proc.pc = (curr->proc.pc + 1) % MEM_SIZE;
			return ;
		}
	}
	if (curr->proc.wait > 0)
		--curr->proc.wait;
	else if (curr->proc.wait == 0)
	{
		select_process_and_execute(curr, head, info->arena, info->color);
		free_instruction(curr->proc.instruct);
		if ((curr->proc.instruct =
			check_operation(info->arena, &curr->proc, info->ref_tab)))
			--curr->proc.wait;
	}
	else
		curr->proc.pc = (curr->proc.pc + 1) % MEM_SIZE;
}

/*
** execute all the process, beginning with the younger.
*/

void					execute_all_process(t_plst **head, t_argv *info)
{
	t_plst		*p;

	p = *head;
	while (p)
	{
		execute_one_process(p, head, info);
		p = p->nxt;
	}
}

/*
** execute the fight and return the winner champ's number.
*/

int						run(t_argv *info)
{
	t_plst			*head;

	head = init_process(*info);
	if (is_there_flag(info->f, _G_) != -1)
		gui(info);
	while (head)
	{
		displaydump(info);
		execute_all_process(&head, info);
		if (info->cycle % info->cycle_to_die == 0 && info->cycle)
		{
			++info->checks;
			process_live(&head);
			if (NBR_LIVE <= count_live(1) || info->checks % MAX_CHECKS == 0)
			{
				if ((info->cycle_to_die -= CYCLE_DELTA) <= 0)
					break ;
				info->checks = 0;
			}
		}
		is_there_flag(info->f, _G_) != -1 ? handle_wait(info, head) : 0;
		++info->cycle;
	}
	delete_all_process(&head);
	return (*last_living_player() == 0 ? n_champ(0) : *(last_living_player()));
}
