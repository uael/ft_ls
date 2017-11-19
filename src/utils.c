/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 20:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

inline uint8_t	ls_err(char const *prg, char const *arg, int err_no)
{
	ft_puts(2, prg);
	ft_puts(2, ": ");
	ft_puts(2, arg);
	ft_puts(2, ": ");
	ft_putl(2, strerror(err_no));
	return (1);
}

inline uint8_t	ls_err_dump(t_ls *ls)
{
	size_t		i;
	size_t		j;
	t_ls_err	tmp;
	t_ls_err	*errs;

	errs = ls->errs.buf;
	j = 0;
	while (++j < ls->errs.len && (i = 0) == 0)
		while (++i < ls->errs.len)
			if (ft_strcmp(errs[i - 1].arg, errs[i].arg) > 0)
			{
				tmp = errs[i - 1];
				errs[i - 1] = errs[i];
				errs[i] = tmp;
			}
	i = 0;
	while (i < ls->errs.len)
	{
		ls_err(ls->p, errs[i].arg, errs[i].err_no);
		++i;
	}
	return (0);
}

inline float	ls_fmt_size(off_t sz, char *unit)
{
	float f;

	*unit = 'M';
	if ((f = sz) < 1000)
		*unit = 'B';
	else if ((f /= 1024) < 1000)
		*unit = 'K';
	else
		f /= 1024;
	return (f);
}

inline uint8_t	ls_opt_error(t_ls *ls, char c)
{
	return ((uint8_t)((ft_puts(1, ls->p) &
		ft_puts(2, ": illegal option -- ") & ft_putc(2, c) &
		ft_puts(2, "\nusage: ") & ft_puts(2, ft_basename(ls->p)) &
		ft_putl(2, " [-1Rahlrt] [file ...]")) > 0));
}

inline uint8_t	ls_opt_parse(uint8_t *opt, char *s, char *c)
{
	while (*++s)
		if ((*c = *s) == 'a')
			*opt |= LS_DOTS;
		else if (*s == 'l')
			*opt |= LS_LONG;
		else if (*s == 'R')
			*opt |= LS_RECU;
		else if (*s == 'r')
			*opt |= LS_REVE;
		else if (*s == 't')
			*opt |= LS_ASCT;
		else if (*s == 'h')
			*opt |= LS_UNIT;
		else if (*s == '1')
			*opt |= LS_LINE;
		else if (*s)
			return (1);
	return (0);
}
