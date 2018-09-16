/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:56:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/09 16:56:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static char	*get_label_name(t_db *db, const char *instruction, size_t *length)
{
	char *label_name;

	while (ft_strchr(LABEL_CHARS, instruction[*length])
		&& instruction[*length] != '\0')
		++(*length);
	if (*length - 1 == 0)
		clean_and_exit(db, "LABEL SYNTAX ERROR IN ARGUMENT");
	label_name = ft_strnew(*length - 1);
	label_name = ft_strncpy(label_name, instruction + 1, *length - 1);
	return (label_name);
}

size_t		handle_direct_argument(t_db *db, const char *instruction, int a_n)
{
	size_t length;

	length = 0;
	if (*instruction != ':' && *instruction != '-' && !ft_isdigit(*instruction))
		clean_and_exit(db, "DIRECT ARGUMENT SYNTAX ERROR IN INSTRUCTION");
	db->bot.instructions[db->inst_counter - 1].args[a_n - 1].type = e_direct;
	if (instruction[length] == ':')
	{
		++length;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].lable = true;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].value = 0;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].label_name =
						get_label_name(db, instruction, &length);
	}
	else
	{
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].lable = false;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].value =
						big_little_endian((uint32_t)ft_atoi(instruction));
		length += instruction[0] == '-' ? 1 : 0;
	}
	return (length);
}

size_t		handle_indirect_argument(t_db *db, const char *inst, int a_n)
{
	size_t l;

	l = 0;
	db->bot.instructions[db->inst_counter - 1].args[a_n - 1].type = e_undirect;
	if (inst[l] == ':')
	{
		++l;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].lable = true;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].value = 0;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].label_name =
				get_label_name(db, inst, &l);
	}
	else
	{
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].lable = false;
		db->bot.instructions[db->inst_counter - 1].args[a_n - 1].value =
				big_little_endian((uint32_t)ft_atoi(inst));
		l += inst[0] == '-' ? 1 : 0;
	}
	return (l);
}

size_t		handle_register_argument(t_db *db, const char *inst, int a_n)
{
	size_t l;
	size_t digits_count;

	l = 1;
	while (ft_iswhitespace(inst[l]))
		++l;
	if (inst[l] != 'r')
		clean_and_exit(db, "WRONG 2nd ARGUMENT IN LD INSTRUCTION");
	++l;
	if (!ft_isdigit(inst[l]))
		clean_and_exit(db, "REGISTER ARGUMENT SYNTAX ERROR IN INSTRUCTION");
	digits_count = 0;
	while (ft_isdigit(inst[l + digits_count]))
		++digits_count;
	if (digits_count > 2)
		clean_and_exit(db, "REGISTER NUMBER CAN'T BE HIGHER THAN 99");
	db->bot.instructions[db->inst_counter - 1].args[a_n - 1].type = e_register;
	db->bot.instructions[db->inst_counter - 1].args[a_n - 1].lable = false;
	db->bot.instructions[db->inst_counter - 1].args[a_n - 1].value =
			big_little_endian((uint32_t)ft_atoi(inst + l));
	l += digits_count;
	return (l);
}
