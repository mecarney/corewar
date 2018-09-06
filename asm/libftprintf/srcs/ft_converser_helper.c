/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converser_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:51:34 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/29 04:15:16 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

char	*fct_precision(char *str, t_var var)
{
	int		i;
	char	*newstr;

	i = -1;
	newstr = ft_strnew(var.precision);
	while (++i < var.precision)
		newstr[i] = str[i];
	return (newstr);
}

char	*fct_wprecision(wchar_t *wstr, t_var var)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = ft_strnew(var.precision);
	var.precision = var.precision - ft_wcharlen(wstr[i]);
	while (var.precision >= 0)
	{
		newstr = ft_appendwchar(newstr, wstr[i]);
		i++;
		var.precision = var.precision - ft_wcharlen(wstr[i]);
	}
	return (newstr);
}

char	*fct_width_new(char *str, t_var var, int len)
{
	int		i;
	int		j;
	int		k;
	char	flags;
	char	*newstr;

	i = -1;
	k = 0;
	flags = ' ';
	newstr = ft_strnew(var.width);
	if (ft_strchr(var.flags, '0') != NULL)
		flags = '0';
	if ((str[0] == '-' || str[0] == '+' || str[0] == ' ')
		&& ft_strchr(var.flags, '0'))
		newstr[0] = str[k++];
	if (ft_strchr(var.flags, '-') == NULL)
		while (--var.width >= len)
			newstr[++i + k] = flags;
	j = -1;
	while (++j < len)
		newstr[++i + k] = str[j + k];
	while (--var.width >= len)
		newstr[++i] = ' ';
	return (newstr);
}

char	*fct_precision_int(char *str, t_var var, int len)
{
	int		i;
	int		j;
	int		k;
	char	*newstr;

	i = -1;
	j = -1;
	k = 0;
	newstr = ft_strnew(var.precision);
	if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
		newstr[0] = str[k++];
	while (var.precision-- >= len)
		newstr[++i + k] = '0';
	while (++j < len)
		newstr[i + j + k] = str[j + k];
	return (newstr);
}

char	*fct_precision_hex(char *str, t_var var, int len, int number)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	*newstr;

	i = 0;
	j = -1;
	k = 0;
	size = var.precision + ((ft_strchr(var.flags, '#') && number != 0) ? 2 : 0);
	len = len - ((ft_strchr(var.flags, '#') && number != 0) ? 2 : 0);
	newstr = ft_strnew(size);
	if (ft_strchr(var.flags, '#') && number != 0)
	{
		newstr[0] = '0';
		newstr[1] = 'x';
		k += 2;
	}
	while (var.precision-- > len)
		newstr[i++ + k] = '0';
	while (++j < len)
		newstr[i + j + k] = str[j + k];
	return (newstr);
}
