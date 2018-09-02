/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_source_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:03:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/08/19 17:03:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	validate_instruction(t_db *db)
{
	char *tmp;

	tmp = db->v_data.line;
	if (!is_instruction(tmp))
		tmp += validate_and_save_lable(db);
	while (ft_iswhitespace(*tmp))
		++tmp;
	if (*tmp == ';' || *tmp == '#' || *tmp == '\0')
		return ;
	if (!is_instruction(tmp))
		clean_and_exit(db, "INSTRUCTION SYNTAX ERROR");
}

static void	validate_line(t_db *db)
{
	char *tmp;

	tmp = db->v_data.line;
	db->v_data.line = ft_strtrim(tmp);
	ft_strdel(&tmp);
	if (db->v_data.line[0] == '#' || db->v_data.line[0] == ';'
			|| ft_strequ(db->v_data.line, ""))
		return ;
	else if (ft_strnequ(db->v_data.line, ".name", 5))
		clean_and_exit(db, "THERE IS ALREADY ONE NAME");
	else if (ft_strnequ(db->v_data.line, ".comment", 8))
		clean_and_exit(db, "THERE IS ALREADY ONE COMMENT");
	validate_instruction(db);
}

static void	read_instructions(t_db *db)
{
	int	gnl_ret_val;

	while ((gnl_ret_val = get_next_line(db->source_fd, &db->v_data.line)))
	{
		++db->v_data.line_counter;
		if (gnl_ret_val == -1)
			clean_and_exit(db, "READING ERROR");
		else if (ft_strequ(db->v_data.line, ""))
			;
		else
			validate_line(db);
		ft_strdel(&db->v_data.line);
	}
	if (db->bot.bot_size == 0)
		clean_and_exit(db, "THERE IS 0 INSTRUCTIONS");
}

void		read_source_file(t_db *db)
{
	read_name_and_comment(db);
	read_instructions(db);
}
