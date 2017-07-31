/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontain <tfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 06:11:08 by tfontain          #+#    #+#             */
/*   Updated: 2017/07/31 06:36:54 by tfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void				fill_process_init(t_plst *cur, int n_champs, int i)
{
	i = n_champs - i - 1;
	cur->proc.instruct = NULL;
	ft_bzero(cur->proc.reg, sizeof(cur->proc.reg));
	cur->proc.pc = (MEM_SIZE / n_champs) * i;
	cur->proc.carry = 0;
	cur->proc.wait = 0;
	cur->proc.instruct = NULL;
	cur->proc.id = i + 1;
	cur->proc.reg[0] = 0xFFFFFFFF - i;
	cur->proc.exec_live = 0;
	cur->nxt = NULL;
}

/*
** init a list with the starting processus, beginning with the last and
** finishing with the first.
*/

t_plst					*init_process(t_argv info)
{
	t_plst				*head;
	t_plst				*cur;
	int					i;

	head = NULL;
	i = 0;
	while (i < info.n_champs)
	{
		if (head == NULL)
		{
			if ((cur = malloc(sizeof(t_plst))) == NULL)
				error(_ERR_STD)(NULL);
			head = cur;
		}
		fill_process_init(cur, info.n_champs, i);
		if (i + 1 == info.n_champs)
			break ;
		if ((cur->nxt = malloc(sizeof(t_plst))) == NULL)
			error(_ERR_STD)(NULL);
		cur = cur->nxt;
		++i;
	}
	return (head);
}

static inline void		delete_process(t_plst *current, t_plst **head)
{
	t_plst				*tmp;

	if (current == *head)
	{
		tmp = current->nxt;
		if (current->proc.instruct)
			free_instruction(current->proc.instruct);
		free(current);
		*head = tmp;
		return ;
	}
	tmp = *head;
	while (tmp->nxt != current)
		tmp = tmp->nxt;
	tmp->nxt = tmp->nxt->nxt;
	if (current->proc.instruct)
		free_instruction(current->proc.instruct);
	free(current);
}

int						process_live(t_plst **head)
{
	t_plst				*cur;
	t_plst				*tmp;

	cur = *head;
	while (cur)
	{
		tmp = cur->nxt;
		if (cur->proc.exec_live == 0)
			delete_process(cur, head);
		else
			cur->proc.exec_live = 0;
		cur = tmp;
	}
	return (0);
}

void					delete_all_process(t_plst **head)
{
	t_plst				*cur;
	t_plst				*tmp;

	cur = *head;
	while (cur)
	{
		tmp = cur->nxt;
		delete_process(cur, head);
		cur = tmp;
	}
	*head = NULL;
}
