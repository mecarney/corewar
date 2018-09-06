/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacques <mjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 17:21:01 by mjacques          #+#    #+#             */
/*   Updated: 2018/08/29 04:16:12 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

# include "../libft/header/libft.h"

typedef struct	s_var
{
	char		*flags;
	int			width;
	int			precision;
	char		*type;
	char		converser;
}				t_var;

void			struct_init(t_var *var);
int				ft_printf(const char *format, ...);
int				dispatch(char **buff, t_var var, va_list ap);
int				handle_null(char *str);

/*
** Argument functions
*/

int				ft_check_type(const char *str, t_var *var);
int				ft_isflag(char c);
int				ft_istype(const char *str, char **type);
int				ft_isconverser(const char *str, char *converser);
char			*check_hexa(char *str, t_var var);

/*
** Converser functions
*/

void			fct_void(char **buff, t_var var, va_list ap);
void			fct_void_edge(char **buff, char *str, t_var var);
char			*number_dispatch(t_var var, va_list ap);
void			number_new(char **buff, t_var var, va_list ap);

void			string_new(char **buff, t_var var, va_list ap);
void			wstring_new(char **buff, t_var var, va_list ap);
void			char_new(char **buff, t_var var, va_list ap);
void			wchar_new(char **buff, t_var var, va_list ap);
void			procent_new(char **buff, t_var var);

char			*ft_itoa_base_long(uint64_t value, int base);
void			number_long(char **buff, t_var var, va_list ap);
void			number_octal(char **buff, t_var var, va_list ap);
void			number_hexa(char **buff, t_var var, va_list ap);

char			*fct_precision(char *str, t_var var);
char			*fct_wprecision(wchar_t *wstr, t_var var);
char			*fct_width_new(char *str, t_var var, int len);
char			*fct_precision_int(char *str, t_var var, int len);
char			*number_flag(char *str, t_var var, int len);

/*
** Helper functions
*/

char			*free_str(char *str, char *newstr);
char			*free_join(char *s1, char *s);
char			*free_append(char *s1, char s);
char			*ft_appendwchar(char *buff, wchar_t c);
char			*fct_precision_hex(char *str, t_var var, int len, int number);

#endif
