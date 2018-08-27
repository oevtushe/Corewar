/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:11:47 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/27 16:56:32 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/op.h"

int		del_cars(t_vm *vm, int ctd, int cycles, int final)
{
	t_carriage *temp;
	t_carriage *temp2;

	temp = vm->cars;
	while (temp)
		if (temp->life == 0 || final)
		{
			if (key_validate(vm->flags.v, 8))
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", temp->num_car, cycles - temp->last_live_cn, ctd);
			if (temp == vm->cars)
			{
				vm->cars = temp->next;
				temp2 = vm->cars;
				free(temp);
				temp = vm->cars;
			}
			else
			{
				temp2->next = temp->next;
				free(temp);
				temp = temp2->next;
			}
		}
		else
		{
			temp->life = 0;
			temp2 = temp;
			temp = temp->next;
		}
	return (0);
}

void add_car(t_carriage **cars, t_carriage *car)
{
	if (*cars)
		car->next = *cars;
	*cars = car;
}

int player_create_car(t_player *players, t_carriage **cars)
{
	int players_count;
	t_carriage	*ncar;
	int i;

	i = 0;
	players_count = count_players(players);
	while (players)
	{
		ncar = (t_carriage *)ft_memalloc(sizeof(t_carriage));

		ncar->pc = i;
		if (*cars)
			ncar->num_car = (*cars)->num_car + 1;
		else
			ncar->num_car = 1;
		ncar->life = 1;
		ncar->count_live = 0;
		//
		ncar->wait = -1;
		//
		ncar->reg[1] = players->num_player;
		ncar->num_player = players->num_player;
		add_car(cars, ncar);
		players = players->next;
		i += ((64 / players_count)) * 64;
	}
	return (0);
}
