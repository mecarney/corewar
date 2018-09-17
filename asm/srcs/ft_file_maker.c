/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_maker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:59:24 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/17 14:05:01 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

int		addindex(t_label *list, int index)
{
	t_line	*tmp;

	tmp = list->line;
	while (tmp != NULL)
	{
		index += tmp->size;
		tmp = tmp->next;
	}
	return (index);
}

int		fillheader(char *line, char *str, int size)
{
	char *uno;
	char *due;

	ft_bzero(str, size + 1);
	uno = ft_strchr(line, '\"');
	due = ft_strrchr(line, '\"');
	if (!uno || !due || due - uno == 0 || (due - uno - 1) > size)
	{
		ft_strdel(&line);
		if (size == PROG_NAME_LENGTH)
			ft_error("ERROR: name too long or unvalid");
		else
			ft_error("ERROR: comment too long or unvalid");
	}
	ft_strncpy(str, (uno + 1), due - uno - 1);
	ft_strdel(&line);
	return (1);
}

void	fillsize(t_label *list, t_header *head)
{
	t_label	*tmplist;
	t_line	*tmpline;

	head->prog_size = 0;
	tmplist = list;
	while (tmplist->next != NULL)
		tmplist = tmplist->next;
	head->prog_size += tmplist->index;
	tmpline = tmplist->line;
	while (tmpline != NULL)
	{
		head->prog_size += tmpline->size;
		tmpline = tmpline->next;
	}
}

void	fillthefile(t_label *list, t_header head, int file)
{
	int i;

	fillsize(list, &head);
	ft_putcharsize_fd(COREWAR_EXEC_MAGIC, file, 4);
	i = -1;
	while (head.prog_name[++i])
		ft_putcharsize_fd(head.prog_name[i], file, 1);
	while (i++ < PROG_NAME_LENGTH + 4)
		ft_putcharsize_fd(0, file, 1);
	ft_putcharsize_fd(head.prog_size, file, 4);
	i = -1;
	while (head.comment[++i])
		ft_putcharsize_fd(head.comment[i], file, 1);
	while (i++ < COMMENT_LENGTH + 4)
		ft_putcharsize_fd(0, file, 1);
	print_op(list, file);
	close(file);
	ft_printf("You create a new Champion: %s\n", head.prog_name);
}

void	addtofile(int openfile, char *namefile)
{
	int			file;
	char		*line;
	t_label		*list;
	t_header	head;

	file = 0;
	list = structlabelinit(NULL);
	while (get_next_line(openfile, &line) > 0)
	{
		if (ft_command_line(line) == 1)
			ft_strdel(&line);
		else if (ft_strstr(line, NAME_CMD_STRING) != NULL)
			file += fillheader(line, head.prog_name, PROG_NAME_LENGTH);
		else if (ft_strstr(line, COMMENT_CMD_STRING) != NULL)
			file += fillheader(line, head.comment, COMMENT_LENGTH);
		else
			makestruct(line, list, file);
	}
	if (!(file = open(namefile, O_RDWR | O_CREAT | O_TRUNC, 0766)))
		ft_error("ERROR: Can't create the file");
	fillthefile(list, head, file);
	structfree(list);
}
