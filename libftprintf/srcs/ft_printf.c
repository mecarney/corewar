/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 17:25:48 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/29 04:14:52 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

void		struct_init(t_var *var)
{
	var->flags = ft_strnew(0);
	var->width = 0;
	var->precision = -1;
	var->type = ft_strnew(0);
	var->converser = 0;
}

int			ft_end(char *buff)
{
	int size;

	size = ft_strlen(buff);
	ft_putstr(buff);
	free(buff);
	return (size);
}

int			ft_printf(const char *format, ...)
{
	int		i;
	t_var	var;
	va_list	ap;
	char	*buff;

	va_start(ap, format);
	buff = ft_strnew(0);
	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] != '\0')
			{
				i = ft_check_type(&format[i + 1], &var) + i;
				if (dispatch(&buff, var, ap) == -1)
					return (-1);
			}
		}
		else
			buff = free_append(buff, format[i]);
	}
	ft_end(buff);
	va_end(ap);
	return (i);
}

int			dispatch(char **buff, t_var var, va_list ap)
{
	char *number;

	if (var.converser == '\0')
		return (-1);
	number = ft_strdup("dDi");
	if (ft_strchr(number, var.converser) != NULL)
		number_new(buff, var, ap);
	if (ft_tolower(var.converser) == 'u')
		number_long(buff, var, ap);
	if (ft_tolower(var.converser) == 'x')
		number_hexa(buff, var, ap);
	if (ft_tolower(var.converser) == 'o')
		number_octal(buff, var, ap);
	if (ft_tolower(var.converser) == 's')
		string_new(buff, var, ap);
	if (ft_tolower(var.converser) == 'c')
		char_new(buff, var, ap);
	if (var.converser == 'p')
		fct_void(buff, var, ap);
	if (var.converser == '%')
		procent_new(buff, var);
	return (0);
}

char		*number_flag(char *str, t_var var, int len)
{
	int		i;
	char	*newstr;

	newstr = ft_strnew(len + 1);
	if (ft_strchr(var.flags, '+'))
		newstr[0] = '+';
	else
		newstr[0] = ' ';
	i = -1;
	while (++i < len + 1)
		newstr[1 + i] = str[i];
	return (newstr);
}
