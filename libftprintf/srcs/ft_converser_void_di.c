/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converser_void_di.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 19:18:05 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/12 20:01:08 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

void		fct_void(char **buff, t_var var, va_list ap)
{
	int		len;
	int		number;
	char	*str;

	str = ft_strdup(ft_itoa_base((int64_t)va_arg(ap, void *), 16));
	len = ft_strlen(str);
	if (len == 0)
		fct_void_edge(buff, str, var);
	else
	{
		number = var.precision + 2;
		if (var.precision == -1 || var.precision <= len)
			number = len + 2;
		if (ft_strchr(var.flags, '-') == NULL)
			while (--var.width >= number)
				*buff = free_append(*buff, ' ');
		*buff = free_join(*buff, "0x");
		if (var.precision != -1 && var.precision > len)
			str = free_str(str, fct_precision_int(str, var, len));
		*buff = free_join(*buff, str);
		while (--var.width >= number)
			*buff = free_append(*buff, ' ');
	}
}

void		fct_void_edge(char **buff, char *str, t_var var)
{
	int	len;
	int	number;

	len = 1;
	number = var.precision + 2;
	if (var.precision == -1 || var.precision <= len)
		number = len + 2;
	if (ft_strchr(var.flags, '-') == NULL)
		while (--var.width >= number)
			*buff = free_append(*buff, ' ');
	*buff = free_join(*buff, "0x");
	if (var.precision != -1 && var.precision > len)
		str = free_str(str, fct_precision_int(str, var, len));
	*buff = free_join(*buff, str);
	*buff = free_append(*buff, '0');
	while (--var.width >= number)
		*buff = free_append(*buff, ' ');
}

char		*number_dispatch(t_var var, va_list ap)
{
	char	*str;

	if (ft_strchr(var.type, 'l') || ft_strchr(var.type, 'j')
		|| var.converser == 'D')
		str = ft_strdup(ft_itoa_base((int64_t)va_arg(ap, int64_t), 10));
	else if (ft_strcmp(var.type, "hh") == 0)
		str = ft_strdup(ft_itoa_base((signed char)va_arg(ap, int64_t), 10));
	else if (ft_strchr(var.type, 'h'))
		str = ft_strdup(ft_itoa_base((short)va_arg(ap, int64_t), 10));
	else if (ft_strchr(var.type, 'z'))
		str = ft_strdup(ft_itoa_base((size_t)va_arg(ap, size_t), 10));
	else
		str = ft_strdup(ft_itoa((int)va_arg(ap, int)));
	return (str);
}

static void	remove_0(t_var var)
{
	int		i;

	i = -1;
	while (var.flags[++i])
	{
		if (var.flags[i] == '0')
			var.flags[i] = '1';
	}
}

void		number_new(char **buff, t_var var, va_list ap)
{
	int		len;
	char	*str;

	str = number_dispatch(var, ap);
	if (*str == 0)
		str = ft_strdup("0");
	len = ft_strlen(str);
	if (ft_strchr(str, '-'))
		len--;
	if (var.precision != -1 && var.precision > len)
		str = free_str(str, fct_precision_int(str, var, len));
	if (var.precision != -1 && var.precision < var.width)
		remove_0(var);
	len = ft_strlen(str);
	if ((ft_strchr(var.flags, ' ') || (ft_strchr(var.flags, '+')))
		&& ft_strchr(str, '-') == NULL)
		str = free_str(str, number_flag(str, var, len));
	if (var.precision == 0 && ft_atoi(str) == 0)
		str = ft_strdup("");
	len = ft_strlen(str);
	if (var.width > len)
		str = free_str(str, fct_width_new(str, var, len));
	*buff = free_join(*buff, str);
}
