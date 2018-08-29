/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:42:23 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/19 15:42:28 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

//int		del_player(t_player **players, int num_player)
//{
//	t_player *temp;
//	t_player *temp2;
//
//	temp = *players;
//	temp2 = NULL;
//	while (temp)
//	{
//		if (temp->num_player == num_player)
//		{
//			if (temp2)
//				temp2->next = temp->next;
//			else
//				*players = temp->next;
//			//free(temp->code);
//			free(temp);
//			return (0);
//		}
//		temp2 = temp;
//		temp = temp->next;
//	}
//	return (1);
//}

int		add_player(t_player **player, int n, char *file_name)
{
	t_player *new;
	t_player *temp;

	temp = *player;
	new = (t_player *)malloc(sizeof(t_player));
	new->next = NULL;
	new->file_name = file_name;
	new->num_player = n;
	new->live = 1;
	if (temp)
	{

		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*player = new;
	return (0);
}

int	read_prog(int fd, unsigned int prog_size, unsigned char **code)
{
	unsigned char *prog;

	prog = (unsigned char *)malloc(prog_size + 1);
	if (read(fd, prog, prog_size + 1) != prog_size)
	{
		free(prog);
		return (-1);
	}
	prog[prog_size + 1] = '\0';
	*code = prog;
	return (0);
}

int read_player(t_player *player, int fd)
{
	read(fd, &player->head, sizeof(t_header));
	ft_byterev_ui32(&player->head.magic);
	if (player->head.magic != COREWAR_EXEC_MAGIC)
	{
		close(fd);
		return  (1);
	}
	ft_byterev_ui32(&player->head.prog_size);
	if (read_prog(fd, player->head.prog_size, &player->code))
	{
		close(fd);
		return  (2);
	}
	if (player->head.prog_size > CHAMP_MAX_SIZE)
	{
		close(fd);
		return  (3);
	}
	close(fd);
	return (0);
}
