/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:37:39 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/19 13:20:34 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asm.h"

t_line	*structlineinit(char *str)
{
	t_line	*new;

	if (!str)
		return (new = NULL);
	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new->str = ft_strdup(str);
	if (!(new->op = (t_op *)malloc(sizeof(t_op))))
		return (NULL);
	new->size = get_index(str, new->op);
	new->next = NULL;
	return (new);
}

t_label	*structlabelinit(char *str)
{
	t_label	*new;

	if (!(new = (t_label *)malloc(sizeof(t_label))))
		return (NULL);
	new->label = str;
	new->line = NULL;
	new->index = 0;
	new->next = NULL;
	return (new);
}

void	ft_addline(char *str, int position, t_label *element)
{
	int		len;
	char	*line;
	t_line	*tmp;

	len = ft_strlen(str);
	line = ft_strmcpy(&str[position], len - position);
	if (element->line)
	{
		tmp = element->line;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = structlineinit(line);
	}
	else
		element->line = structlineinit(line);
	ft_strdel(&line);
	ft_strdel(&str);
}

int		ft_addlabel(char *str, char **element)
{
	int		point;
	char	*tmp;

	point = 0;
	if ((tmp = ft_strchr(str, ':')) != NULL)
	{
		if ((point = (tmp - str)) > 0 && str[point - 1] != '%'
			&& ft_strchr(LABEL_CHARS, str[point - 1]))
			*element = ft_strmcpy(str, point);
		point = ((!ft_strchr(LABEL_CHARS, str[point - 1])) ? 0 : point + 1);
	}
	return (point);
}

void	makestruct(char *str, t_label *list, int nbr)
{
	int			position;
	char		*element;

	if (nbr != 2)
		ft_error("ERROR: Invalid header");
	element = NULL;
	while (list->next != NULL)
		list = list->next;
	if ((position = ft_addlabel(str, &element)) > 0)
	{
		if (list->line == NULL && list->label == NULL)
			list->label = ft_checklabel(element);
		else
		{
			list->next = structlabelinit(element);
			list->next->index = addindex(list, list->index);
			list = list->next;
		}
	}
	while (str[position] && ft_isspace(str[position]))
		position++;
	if (str[position] && str[position] != '#')
		ft_addline(str, position, list);
}
