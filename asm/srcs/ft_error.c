/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 20:44:22 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/29 03:45:56 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_asm.h"

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(-1);
}

void	check_parameter(int i, char **line)
{
	int		j;
	int		len;
	char	*tmp;

	tmp = *line;
	len = ft_strlen(g_tab[i].op_name);
	j = -1;
	while (*tmp && ++j < len)
		tmp++;
	while (*tmp && ft_isspace(*tmp))
		tmp++;
	if (!*tmp)
		ft_error("ERROR: No parameter");
	len = 1;
	while (*tmp && *tmp != COMMENT_CHAR)
	{
		if (*tmp == ',')
			len += 1;
		tmp++;
	}
	if (len != g_tab[i].arg_nbr)
		ft_error("ERROR: Wrong number of parameters");
}

void	ft_checkline(char **line)
{
	while (**line && ft_isspace(**line))
		line++;
	if (**line && **line != COMMENT_CHAR)
		ft_error("ERROR: Wrong syntax for the op_code");
}

int		ft_command_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] == COMMENT_CHAR || str[i] == '\0')
		return (1);
	return (0);
}

void	ft_printstruct(t_label *label)
{
	t_label	*tmp;
	t_line	*tmpline;

	tmp = label;
	while (tmp != NULL)
	{
		ft_printf("%s | %d\n", tmp->label, tmp->index);
		tmpline = tmp->line;
		while (tmpline != NULL)
		{
			ft_printf("\t%s | %d\n", tmpline->str, tmpline->size);
			tmpline = tmpline->next;
		}
		tmp = tmp->next;
	}
}
