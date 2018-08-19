/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_and.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:39:30 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/18 18:51:24 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		dsp_and(t_carriage *carriage, unsigned char *map)
{
	unsigned char	acb;
	int				res;
	t_args			args;
	unsigned int	and;

	res = 0;
	acb = map[carriage->pc + 1];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, &args, (t_reader){read_int_from_map, read_short_from_map});
		if ((acb & ARG_MASK1) && (acb & ARG_MASK2) && CHECK_REG(args.arg3.type, args.arg3.readed))
		{
			init_args(carriage, map, &args);
			and = args.arg1.value & args.arg2.value;
			carriage->reg[args.arg3.readed] = and;
			carriage->carry = and ? 0 : 1;
			res = 1;
		}
		carriage->pc += 1 + args.arg1.size + args.arg2.size + args.arg3.size;
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	return (res);
}