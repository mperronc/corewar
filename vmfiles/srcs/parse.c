/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontain <tfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 20:35:26 by tfontain          #+#    #+#             */
/*   Updated: 2017/07/31 13:36:30 by tfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static inline char		*to_memory(const char *arg,
		t_header *champs, int n_players, int n)
{
	static char			arena[MEM_SIZE] = {0};

	open_file(arg, arena + (MEM_SIZE / n_players) * n, champs + n);
	return (arena);
}

static inline void		case_flag(int *ac, const char **av[], t_argv *ret,
		int *n)
{
	if ((**av)[1] == 'n' || (**av)[1] == 's' || (**av)[1] == 'd')
	{
		if ((**av)[1] == 'n')
			*n = ft_atoi((*av)[1]);
		else
		{
			if (ret->f.n != 0)
				error(_ERR_USAGE)();
			ret->f.flag |= ((**av)[1] == 'd' ? _D_ : _S_);
			ret->f.n = ft_atoi((*av)[1]);
		}
		--*ac;
		++*av;
	}
	else if ((**av)[1] == 'g')
		ret->f.flag |= _G_;
}

static inline void		case_player(int *n, t_argv ret, const char *av[],
		const char *champs[])
{
	if (*n != -1)
	{
		if (*n > ret.n_champs || champs[*n - 1] != *av)
			error(_ERR_BAD_NFLAG)();
		*n = -1;
	}
	else
	{
		*n = 0;
		while (champs[*n] != NULL)
			++*n;
		champs[*n] = *av;
		*n = -1;
	}
}

static inline void		load_memory(t_argv *ret, const char *champs[])
{
	int		n;

	n = 0;
	while (n < ret->n_champs)
	{
		ret->arena = to_memory(champs[n], ret->champ, ret->n_champs, n);
		++n;
	}
}

t_argv					*parse(int ac, const char *av[])
{
	static t_argv		ret;
	const char			*champs[MAX_PLAYERS];
	int					n;

	n = -1;
	++av;
	--ac;
	ft_bzero(&ret, sizeof(ret));
	ret.n_champs = count_champions(ac, av, champs);
	ret.n_champs > MAX_PLAYERS ? error(_ERR_TOO_MANY_CH)() : 0;
	ret.n_champs == 0 ? error(_ERR_USAGE)() : 0;
	while (ac > 0)
	{
		if ((*av)[0] == '-' && (*av)[2] == 0)
			case_flag(&ac, &av, &ret, &n);
		else
			case_player(&n, ret, av, champs);
		++av;
		--ac;
	}
	load_memory(&ret, champs);
	if (ret.f.flag & _G_)
		ret.color = init_color_arena(&ret);
	ret.ref_tab = get_ref_tab();
	return (&ret);
}
