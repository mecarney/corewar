/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arguments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 21:38:24 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/29 04:15:19 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_printf.h"

int		ft_check_type(const char *str, t_var *var)
{
	int	i;

	i = -1;
	struct_init(var);
	while (ft_isflag(str[++i]) == 1)
		var->flags = free_append(var->flags, str[i]);
	var->width = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]) != 0)
		i++;
	if (str[i] == '.')
	{
		var->precision = ft_atoi(&str[++i]);
		while (ft_isdigit(str[i]) != 0)
			i++;
	}
	i = ft_istype(&str[i], &var->type) + i;
	i = ft_isconverser(&str[i], &var->converser) + i;
	return (i);
}

int		ft_isflag(char c)
{
	if (c == '#' || c == ' ' || c == '+' || c == '-' || c == '0')
		return (1);
	return (0);
}

int		ft_istype(const char *str, char **type)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strnew(0);
	if (str[i] == 'l' || str[i] == 'h' || str[i] == 'j' || str[i] == 'z')
	{
		tmp = free_append(tmp, str[i]);
		i++;
		if (str[i - 1] == 'l' && str[i] == 'l')
		{
			tmp = free_append(tmp, str[i]);
			i++;
		}
		if (str[i - 1] == 'h' && str[i] == 'h')
		{
			tmp = free_append(tmp, str[i]);
			i++;
		}
		*type = tmp;
	}
	return (i);
}

int		ft_isconverser(const char *str, char *converser)
{
	int		i;
	char	*type;

	i = 0;
	type = ft_strdup("sSpdDioOuUxXcC%%");
	if (ft_strchr(type, str[i]) != NULL)
	{
		*converser = str[i];
		i++;
	}
	return (i);
}
