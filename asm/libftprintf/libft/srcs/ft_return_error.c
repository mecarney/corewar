/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <mcarney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 07:09:42 by mcarney           #+#    #+#             */
/*   Updated: 2018/08/31 13:47:43 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int		ft_return_error(char const *str)
{
	ft_putendl(str);
	exit(EXIT_FAILURE);
}
