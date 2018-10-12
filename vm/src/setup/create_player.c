/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamak <msamak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:26:08 by msamak            #+#    #+#             */
/*   Updated: 2018/10/12 21:23:12 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** *****************************************************************************
** checks if the champion is too long
** *****************************************************************************
*/

static int		check_end_file(t_player *new, char *file)
{
	int i;

	i = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH + new->prog_size;
	while (i < FILE_LEN_MAX)
	{
		if (file[i] != 0)
			return (1);
		i++;
	}
	return (0);
}

/*
** *****************************************************************************
** initializes the player structure
** *****************************************************************************
*/

static t_player	*assignate_value(char *file)
{
	t_player	*new;
	char		*command_size;

	if (!(new = (t_player*)ft_memalloc(sizeof(t_player))))
		exit_corewar(MALLOC_ERROR);
	if (!(new->name = ft_strndup(file + 4, PROG_NAME_LENGTH)))
		exit_corewar(MALLOC_ERROR);
	if (!(command_size = ft_strndup(file + 8 + PROG_NAME_LENGTH, 4)))
		exit_corewar(MALLOC_ERROR);
	new->prog_size = tab_to_int(command_size);
	ft_strdel(&command_size);
	if (!(new->comment = ft_strndup(file + 12 + PROG_NAME_LENGTH, \
		COMMENT_LENGTH)))
		exit_corewar(MALLOC_ERROR);
	if (!(new->instruction = ft_strndup(file + 16 + PROG_NAME_LENGTH + \
		COMMENT_LENGTH, new->prog_size)))
		exit_corewar(MALLOC_ERROR);
	if (check_end_file(new, file) == 1)
		exit_corewar(WRONG_COMMAND_LENGTH);
	new->last_live = 0;
	new->curr_live = 0;
	return (new);
}

/*
** *****************************************************************************
** adds one player
** *****************************************************************************
*/

int				init_player(t_global *info, char *file, char has_pnumber)
{
	t_player	*tmp;
	t_player	*new;

	tmp = info->player;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = assignate_value(file);
	if (!tmp)
		info->player = new;
	else
		tmp->next = new;
	if (has_pnumber)
		new->player = info->next_pnumber;
	else
		new->player = info->player_count + 1;
	info->player_count++;
	return (0);
}
