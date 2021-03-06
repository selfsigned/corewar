/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xperrin <xperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:22:30 by xperrin           #+#    #+#             */
/*   Updated: 2018/10/31 02:07:27 by xperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Updates the player infos
** PL_FMT: Player ID, Player Name, Last Live, Nbr of lives in cycle
*/

static void		u_text_players(t_gtkinfo *i)
{
	GtkTextIter	end;
	gchar		*buf;
	t_player	*p;

	p = i->vm->player_head;
	gtk_text_buffer_set_text(i->t.play, "", -1);
	gtk_text_buffer_get_start_iter(i->t.play, &end);
	while (p)
	{
		if (!(buf = g_strdup_printf(PL_FMT, p->pnumber, p->name,
					p->last_live, p->curr_live)))
			exit_corewar(MALLOC_ERROR);
		gtk_text_buffer_insert(i->t.play, &end, buf, -1);
		g_free(buf);
		p = p->next;
	}
}

static void		map_memtxt_insert(int pnum, int *col, t_map *map, t_gtkinfo *i)
{
	char		*hexa;
	GtkTextIter	end;

	gtk_text_buffer_get_end_iter(i->t.mem, &end);
	if (!(hexa = ft_itoa_u(map->c, 16, 0)))
		exit_corewar(MALLOC_ERROR);
	if (ft_strlen(hexa) == 1)
		append_in_mem_buf("0", pnum, map, i);
	append_in_mem_buf(hexa, pnum, map, i);
	gtk_text_buffer_get_end_iter(i->t.mem, &end);
	if (*col == 64)
	{
		*col = 0;
		gtk_text_buffer_insert(i->t.mem, &end, "\n", -1);
	}
	else
		gtk_text_buffer_insert(i->t.mem, &end, " ", -1);
	free(hexa);
}

static void		u_text_map(t_gtkinfo *i)
{
	int			curmap;
	int			col;
	t_map		*map;
	t_pnum		pnum;

	gtk_text_buffer_set_text(i->t.mem, "", -1);
	map = i->vm->map;
	col = 1;
	curmap = -1;
	while (++curmap < MEM_SIZE)
	{
		pnum = get_map_pnum(map);
		map_memtxt_insert(pnum, &col, map, i);
		col++;
		map = map->next;
	}
}

static void		u_cycle_label(t_gtkinfo *i)
{
	gchar		*buf;

	if (!(buf = g_strdup_printf("Cycles: %d", i->vm->clock.cycle)))
		exit_corewar(MALLOC_ERROR);
	gtk_label_set_text(i->c.cycles, buf);
	g_free(buf);
}

gboolean		u_text(t_gtkinfo *i)
{
	static unsigned int cycle = 1;

	if (!i->b.pause && i->b.run)
		gtk_spinner_start(i->c.spin);
	else
		gtk_spinner_stop(i->c.spin);
	if (cycle != i->vm->clock.cycle)
	{
		u_cycle_label(i);
		u_text_players(i);
		u_text_map(i);
		if (i->b.pause)
			gtk_button_set_label(i->c.pause, PAUSE_STOPPED_MSG);
	}
	else if (!i->b.run)
		u_text_players(i);
	cycle = i->vm->clock.cycle;
	return (G_SOURCE_CONTINUE);
}
