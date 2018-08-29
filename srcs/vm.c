/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:22:51 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/28 19:07:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void init_vm(t_vm *vm)
{
	vm->flags.n = -1;
	//vm->game_cycle = 1;
}

int ft_usage()
{
	ft_printf("Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n"
					  "    -a        : Prints output from \"aff\" (Default is to hide it)\n"
					  "#### TEXT OUTPUT MODE ##########################################################\n"
					  "    -d N      : Dumps memory after N cycles then exits\n"
					  "    -s N      : Runs N cycles, dumps memory, pauses, then repeats\n"
					  "    -v N      : Verbosity levels, can be added together to enable several\n"
					  "                - 0 : Show only essentials\n"
					  "                - 1 : Show lives\n"
					  "                - 2 : Show cycles\n"
					  "                - 4 : Show operations (Params are NOT litteral ...)\n"
					  "                - 8 : Show deaths\n"
					  "                - 16 : Show PC movements (Except for jumps)\n"
					  "#### BINARY OUTPUT MODE ########################################################\n"
					  "    -b        : Binary output mode for corewar.42.fr\n"
					  "    --stealth : Hides the real contents of the memory\n"
					  "#### NCURSES OUTPUT MODE #######################################################\n"
					  "    -n        : Ncurses output mode\n"
					  "    --stealth : Hides the real contents of the memory\n"
					  "################################################################################\n");
	return (0);
}

int main(int argc, char **argv)
{

	t_vm	vm;

	if (argc < 2)
		ft_usage();
	ft_memset(&vm, 0, sizeof(t_vm));
	init_vm(&vm);
	read_argv(&vm, argc, argv);
	write_in_map(vm.map, vm.players);
	player_create_car(vm.players , &vm.cars);
	//print_map(vm.map);

//	while(vm.cars)
//	{
//		ft_printf("pc = %d\n", vm.cars->pc);
//		ft_printf("num_player = %d\n", vm.cars->num_player);
//		vm.cars = vm.cars->next;
//	}

	play_while(&vm);
	//key_validate(8, 4);

	free_all(&vm);
	return (0);
}

