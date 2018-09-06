/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helperfunctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:50:27 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/12 20:01:10 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

int		handle_null(char *str)
{
	if (str == NULL)
		return (-1);
	return (ft_strlen(str));
}

char	*free_str(char *str, char *newstr)
{
	ft_strdel(&str);
	str = newstr;
	return (str);
}

char	*free_join(char *s1, char *s)
{
	char *tmp;

	tmp = ft_strjoin(s1, s);
	ft_strdel(&s1);
	s1 = tmp;
	return (s1);
}

char	*free_append(char *s1, char s)
{
	char *tmp;

	tmp = ft_strappend(s1, s);
	ft_strdel(&s1);
	s1 = tmp;
	return (s1);
}

char	*ft_appendwchar(char *buff, wchar_t c)
{
	if (c <= 0x7f)
		buff = ft_strappend(buff, c);
	else if (c <= 0x7ff)
	{
		buff = ft_strappend(buff, (c >> 6) + 0xC0);
		buff = ft_strappend(buff, (c & 0x3f) + 0x80);
	}
	else if (c <= 0xffff)
	{
		buff = ft_strappend(buff, (c >> 12) + 0xE0);
		buff = ft_strappend(buff, (c >> 6 & 0x3F) + 0x80);
		buff = ft_strappend(buff, (c & 0x3F) + 0x80);
	}
	else if (c <= 0x10ffff)
	{
		buff = ft_strappend(buff, (c >> 18) + 0xF0);
		buff = ft_strappend(buff, ((c >> 12) & 0x3F) + 0x80);
		buff = ft_strappend(buff, ((c >> 6) & 0x3F) + 0x80);
		buff = ft_strappend(buff, (c & 0x3F) + 0x80);
	}
	return (buff);
}
