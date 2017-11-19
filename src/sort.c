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

static t_bool	ls_entry_dtyswap(t_ls_entry *a, t_ls_entry *b, uint8_t o,
	t_bool r)
{
	int64_t c;

	if (r && LS_ISDIR(a) != LS_ISDIR(b))
		return ((t_bool)!LS_ISDIR(b));
	if ((o & LS_ASCT) && (c = I64CMP(b->stat.st_mtime, a->stat.st_mtime)) != 0)
		return ((t_bool)((o & LS_REVE) ? c < 0 : c > 0));
	if ((c = ft_strcmp(a->path, b->path)) == 0)
		return (0);
	return ((t_bool)((o & LS_REVE) ? c < 0 : c > 0));
}

uint8_t			ls_entry_sort(t_ls_entry *ent, size_t n, uint8_t opt, t_bool r)
{
	size_t		i;
	size_t		j;
	t_ls_entry	tmp;
	t_bool		s;

	j = 0;
	s = 0;
	while (++j < n && !s)
	{
		i = 0;
		s = 0;
		while (++i < n)
			if (ls_entry_dtyswap(ent + i - 1, ent + i, opt, r))
			{
				tmp = ent[i - 1];
				ent[i - 1] = ent[i];
				ent[i] = tmp;
				s = 1;
			}
	}
	return (0);
}
