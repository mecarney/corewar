/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converser_c_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:49:53 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/12 20:01:02 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

void	string_new(char **buff, t_var var, va_list ap)
{
	int		len;
	char	*str;

	if (var.converser == 'S' || (var.type[0] == 'l' && var.type[1] == '\0'))
		wstring_new(buff, var, ap);
	else
	{
		str = (char *)va_arg(ap, wchar_t *);
		if (handle_null(str) == -1)
			*buff = free_join(*buff, "(null)");
		else
		{
			str = ft_strdup(str);
			len = ft_strlen(str);
			if (var.precision != -1 && var.precision < len)
				str = free_str(str, fct_precision(str, var));
			len = ft_strlen(str);
			if (var.width > len)
				str = free_str(str, fct_width_new(str, var, len));
			*buff = free_join(*buff, str);
		}
	}
}

void	wstring_new(char **buff, t_var var, va_list ap)
{
	int		i;
	int		len;
	wchar_t	*wstr;
	char	*str;

	wstr = (wchar_t *)va_arg(ap, wchar_t *);
	if (handle_null((char *)wstr) == -1)
		*buff = free_join(*buff, "(null)");
	else
	{
		len = ft_wstrlen(wstr);
		str = ft_strnew(len);
		i = -1;
		while (++i < len)
			str = free_str(str, ft_appendwchar(str, wstr[i]));
		str[i] = '\0';
		if (var.precision != -1 && var.precision < len)
			str = free_str(str, fct_wprecision(wstr, var));
		len = ft_strlen(str);
		if (var.width > len)
			str = free_str(str, fct_width_new(str, var, len));
		*buff = free_join(*buff, str);
	}
}

void	char_new(char **buff, t_var var, va_list ap)
{
	char	*str;

	if (var.converser == 'C' || (var.type[0] == 'l' && var.type[1] == '\0'))
		wchar_new(buff, var, ap);
	else
	{
		str = ft_strnew(1);
		str[0] = (char)va_arg(ap, int);
		if (var.width > 1)
			str = free_str(str, fct_width_new(str, var, 1));
		*buff = free_join(*buff, str);
	}
}

void	wchar_new(char **buff, t_var var, va_list ap)
{
	int		len;
	char	*str;
	wchar_t	c;

	c = (wchar_t)va_arg(ap, wchar_t);
	len = ft_wcharlen(c);
	str = ft_strnew(len);
	str = free_str(str, ft_appendwchar(str, c));
	str[len] = '\0';
	len = ft_strlen(str);
	if (var.width > len)
		str = free_str(str, fct_width_new(str, var, len));
	*buff = free_join(*buff, str);
}

void	procent_new(char **buff, t_var var)
{
	char	*str;

	str = ft_strdup("%");
	if (var.width > 1)
		str = free_str(str, fct_width_new(str, var, 1));
	*buff = free_join(*buff, str);
}
