/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <rbarbazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 11:24:59 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/09/10 15:43:08 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_sfile
{
	char			*line;
	struct s_sfile	*next;
}					t_sfile;

/*
** store sfile
*/

int	store_sfile(char *filename, t_sfile **sfile);

/*
** display
*/

void	display_sfile(t_sfile *sfile);

/*
** clear
*/

void	free_asm(t_sfile *sfile);

#endif