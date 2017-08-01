/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bytohex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperronc <mperronc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 20:28:00 by mperronc          #+#    #+#             */
/*   Updated: 2017/07/31 21:36:06 by mperronc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static char			ft_hex_digit(unsigned n, t_bool big_or_little)
{
	if (n < 10)
		return (n + '0');
	else if (big_or_little)
		return ((n - 10) + 'a');
	else
		return ((n - 10) + 'A');
}

const char			*ft_bytohex(unsigned char o, t_bool big_or_little)
{
	static char		hex[3];

	hex[0] = ft_hex_digit(o / 0x10, big_or_little);
	hex[1] = ft_hex_digit(o % 0x10, big_or_little);
	hex[2] = 0;
	return (hex);
}
