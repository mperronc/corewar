/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfontain <tfontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 13:35:35 by tfontain          #+#    #+#             */
/*   Updated: 2017/07/31 10:06:31 by tfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static inline void		errorn(int n, const char *av[], const char *champs[])
{
	if ((*av)[1] == 'n')
	{
		if (n < 1 || n > MAX_PLAYERS
				|| champs[n - 1] != NULL)
			error(_ERR_BAD_NFLAG)();
		champs[n - 1] = av[2];
	}
}

int						count_champions(int ac, const char *av[],
		const char **champs)
{
	int					n;

	ft_bzero(champs, sizeof(char *) * MAX_PLAYERS);
	n = ac;
	while (ac > 0)
	{
		if ((*av)[0] == '-' && (*av)[2] == 0)
		{
			if ((*av)[1] == 'n' || (*av)[1] == 's' || (*av)[1] == 'd')
			{
				if (ac <= 1 || ((*av)[1] == 'n' && ac <= 2))
					error(_ERR_USAGE)();
				errorn(ft_atoi(av[1]), av, champs);
				--n;
				--n;
				--ac;
				++av;
			}
			else if ((*av)[1] == 'g')
				--n;
		}
		--ac;
		++av;
	}
	return (n);
}
