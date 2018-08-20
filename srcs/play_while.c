
#include "../includes/op.h"

int		check_live()
{

}

int play_cycle(t_vm *vm)
{
	t_carriage	*tcars;
	int				(*dsp[16])(t_carriage*, unsigned char*);

	while (cycle)
	{
		tcars = vm->cars;

		while (tcars)
		{
			dsp[vm->map[tcars->pc] - 1](tcars, map);
			if (vm->map[tcars] == 1)
				vm->players->live;
		}

		cycle--;
	}
}

int play_while(t_vm *vm)
{
	int 		cycle;
	int 		cycle_to_die;
	int 		count_cycle;
	int 		count_live;

	count_cycle = 0;
	cycle_to_die = CYCLE_TO_DIE;

	while ((count_live = check_live(vm->players)))
	{
		cycle = cycle_to_die;
		if (count_cycle == MAX_CHECKS || count_live > NBR_LIVE)
			cycle_to_die /= CYCLE_DELTA;

		play_cycle(vm);
//		while (cycle)
//		{
//			cycle--;
//		}
		count_cycle++;
	}
}

int play_start(t_vm *vm)
{

}