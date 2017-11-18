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

static int	ls_entry_strcmp(t_ls_entry *a, t_ls_entry *b)
{
	return (ft_strcmp(a->path, b->path));
}

static int	ls_entry_timecmp(t_ls_entry *a, t_ls_entry *b)
{
	int r;

	r = -I64CMP(a->stat.st_ctime, b->stat.st_ctime);
	return (r != 0 ? r : ls_entry_strcmp(a, b));
}


void		ls_entry_sort(t_ls_entry *self, size_t n, uint8_t opt)
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
