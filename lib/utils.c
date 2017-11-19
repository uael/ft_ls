/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 20:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

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
		else if (*s)
			return (1);
	return (0);
}

static int		ls_entry_strcmp(t_ls_entry *a, t_ls_entry *b)
{
	return (ft_strcmp(a->path, b->path));
}

static int		ls_entry_timecmp(t_ls_entry *a, t_ls_entry *b)
{
	int r;

	r = -I64CMP(a->stat.st_ctime, b->stat.st_ctime);
	return (r != 0 ? r : ls_entry_strcmp(a, b));
}


void			ls_entry_sort(t_ls_entry *self, size_t n, uint8_t opt)
{
	size_t		i;
	size_t		j;
	int			c;
	t_ls_entry	tmp;

	(void) opt;
	j = 0;
	while (++j < n && (i = 0) == 0)
		while (++i < n)
		{
			if ((opt & LS_ASCT) &&
				(c = ls_entry_timecmp(self + i - 1, self + i)) == 0)
				continue ;
			if (!(opt & LS_ASCT) &&
				(c = ls_entry_strcmp(self + i - 1, self + i)) == 0)
				continue ;
			if ((opt & LS_REVE) && c > 0)
				continue ;
			if (!(opt & LS_REVE) && c < 0)
				continue ;
			tmp = self[i - 1];
			self[i - 1] = self[i];
			self[i] = tmp;
		}
}
