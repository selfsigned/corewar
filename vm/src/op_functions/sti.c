/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <rbarbazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 22:37:46 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/10/27 13:33:54 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	debug_sti(t_process *process, int param1, int param2,\
short param_sum)
{
	ft_printf("P%5d | sti r%d %d %d\n", process->process_nb,\
		process->curr_op.param[0], param1, param2);
	ft_printf("       | -> store to %hd + %hd = %d", param1, param2,\
		param1 + param2);
	ft_printf(" (with pc and mod %hd)\n", (param_sum + process->op_pos)\
		% MEM_SIZE);
}

void		sti(t_global *info, t_process *process)
{
	int		param0;
	int		param1;
	int		param2;
	short	param_sum;

	param0 = 0;
	param1 = 0;
	param2 = 0;
	if (get_param_value(info, process, 0, &param0))
		return ;
	if (get_param_value(info, process, 1, &param1))
		return ;
	if (get_param_value(info, process, 2, &param2))
		return ;
	param_sum = (short)(param1 + param2) % IDX_MOD;
	if (param_sum < 0)
		param_sum = MEM_SIZE + param_sum;
	if (info->debug)
		debug_sti(process, param1, param2, param_sum);
	write_at_position(info->map, process, param_sum + process->op_pos, param0);
}
