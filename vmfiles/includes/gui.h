/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperronc <mperronc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:31:06 by mperronc          #+#    #+#             */
/*   Updated: 2017/08/02 00:30:30 by mperronc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "vm.h"

# define AW				64 * 3 + 1
# define AH				64 + 2
# define IW				60
# define IH				16
# define CW				133
# define CH				4
# define PW				48
# define PH				10
# define WPH			8

# define P1_COLOR 		COLOR_RED
# define P2_COLOR 		COLOR_GREEN
# define P3_COLOR 		COLOR_YELLOW
# define P4_COLOR 		COLOR_BLUE
# define N_COLOR		COLOR_WHITE

# define DEBUG_MAX_PROC	24

# define STEP			1
# define INSTANT		-1

typedef struct			s_gui
{
	WINDOW				*win_arena;
	WINDOW				*win_vm_info;
	WINDOW				**win_champions;
	WINDOW				**wlist_process;
	int					debug;
	int					mode;
}						t_gui;

#endif
