/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converser_o_u_x.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:53:17 by mjacques          #+#    #+#             */
/*   Updated: 2018/09/07 15:30:31 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

char			*ft_itoa_base_long(uint64_t value, int base)
{
	static char	basetab[] = "0123456789abcdef";
	char		*nstr;
	int			i;
	uint64_t	nbr;

	nbr = value;
	i = 1;
	while (nbr > 0)
	{
		nbr = nbr / base;
		i++;
	}
	nstr = ft_strnew(i);
	nstr = (nstr + i + 1);
	while (value)
	{
		*--nstr = basetab[value % base];
		value = value / base;
	}
	return (nstr);
}

void			number_long(char **buff, t_var var, va_list ap)
{
	int			len;
	uint64_t	number;
	char		*str;

	str = ft_strnew(0);
	number = (uint64_t)va_arg(ap, uint64_t);
	if (*var.type == 0)
		str = ft_strdup(ft_itoa_base_long((unsigned int)number, 10));
	else if (ft_strchr(var.type, 'l') || var.converser == 'U')
		str = ft_strdup(ft_itoa_base_long((unsigned long)number, 10));
	else if (ft_strchr(var.type, 'j'))
		str = ft_strdup(ft_itoa_base_long((size_t)number, 10));
	else
		str = ft_strdup(ft_itoa_base_long(number, 10));
	if (number == 0 || *str == '\0')
		str = ft_strdup("0");
	len = ft_strlen(str);
	if (var.precision != -1 && var.precision > len)
		str = free_str(str, fct_precision_int(str, var, len));
	if (var.width > len)
		str = free_str(str, fct_width_new(str, var, len));
	*buff = free_join(*buff, str);
}

void			number_octal(char **buff, t_var var, va_list ap)
{
	int			len;
	int64_t		number;
	char		*str;

	str = ft_strnew(0);
	number = (int64_t)va_arg(ap, int64_t);
	if (number >= 0 && ft_strchr(var.flags, '#'))
		str = ft_strdup("0");
	str = free_join(str, ft_itoa_base(number, 8));
	len = ft_strlen(str);
	if (var.precision != -1 && var.precision > len)
		str = free_str(str, fct_precision_int(str, var, len));
	if (number == 0)
		str = ft_strdup("0");
	if (number == 0 && var.precision == 0)
		str = ft_strdup("");
	if (number >= 0 && ft_strchr(var.flags, '#') && var.precision == 0)
		str = ft_strdup("0");
	len = ft_strlen(str);
	if (var.width > len)
		str = free_str(str, fct_width_new(str, var, len));
	*buff = free_join(*buff, str);
}

static char		*ft_strtoupper(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
	return (str);
}

void			number_hexa(char **buff, t_var var, va_list ap)
{
	int			len;
	uint64_t	number;
	char		*str;

	str = ft_strnew(0);
	number = (uint64_t)va_arg(ap, uint64_t);
	if (ft_strchr(var.flags, '#') && number != 0)
		str = ft_strdup("0x");
	if (*var.type == 0 || ft_strchr(var.type, 'h'))
		str = free_join(str, ft_itoa_base((unsigned int)number, 16));
	else
		str = free_join(str, ft_itoa_base(number, 16));
	len = ft_strlen(str);
	if (var.precision != -1)
		str = free_str(str, fct_precision_hex(str, var, len, number));
	len = ft_strlen(str);
	if (len == 0 || (number == 0 && var.precision == -1))
		str = ft_strdup("0");
	if (var.precision == 0)
		str = ft_strdup("");
	if (var.converser == 'X')
		str = ft_strtoupper(str);
	if (var.width > len)
		str = free_str(str, fct_width_new(str, var, len));
	*buff = free_join(*buff, str);
}
