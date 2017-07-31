/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 02:58:39 by tfontain          #+#    #+#             */
/*   Updated: 2017/07/31 06:36:40 by tfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** add a forked process to the start of the list by copy (he become the head)
** because the last process is the first to be executed.
*/

void		fork_process(t_plst **head, t_plst *to_fork, int pc)
{
	t_plst	*new;

	if ((new = malloc(sizeof(t_plst))) == NULL)
		error(_ERR_STD)(NULL);
	ft_memcpy(new->proc.reg, to_fork->proc.reg, sizeof(to_fork->proc.reg));
	new->proc.pc = pc;
	new->proc.carry = to_fork->proc.carry;
	new->proc.wait = 0;
	new->proc.instruct = NULL;
	new->proc.id = to_fork->proc.id;
	new->proc.exec_live = to_fork->proc.exec_live;
	new->nxt = *head;
	*head = new;
}

int			op_fork(t_plst *self, t_plst **head, t_instruct *instruct)
{
	int		npc;

	npc = mod(self->proc.pc + (instruct->args[0] % IDX_MOD), MEM_SIZE);
	fork_process(head, self, npc);
	self->proc.pc = (self->proc.pc + instruct->size) % MEM_SIZE;
	return (1);
}

int			op_lfork(t_plst *self, t_plst **head, t_instruct *instruct)
{
	int		npc;

	npc = mod(self->proc.pc + instruct->args[0], MEM_SIZE);
	fork_process(head, self, npc);
	self->proc.pc = (self->proc.pc + instruct->size) % MEM_SIZE;
	return (1);
}
