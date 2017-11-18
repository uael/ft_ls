/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 16:53:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ent.h"

static int	ls_ent_sort_alpha(t_ls_ent *a, t_ls_ent *b)
{
	return (ft_strcmp(a->path, b->path));
}

static int	ls_ent_sort_time(t_ls_ent *a, t_ls_ent *b)
{
	int r;

	r = -I64CMP(a->stat.st_ctime, b->stat.st_ctime);
	return (r != 0 ? r : ls_ent_sort_alpha(a, b));
}


void		ls_ent_sort(t_ls_ent *self, size_t n, uint8_t opt)
{
	size_t		i;
	size_t		j;
	int			c;
	t_ls_ent	tmp;

	(void) opt;
	j = 0;
	while (++j < n && (i = 0) == 0)
		while (++i < n)
		{
			if ((opt & FT_LS_ASCT) &&
				(c = ls_ent_sort_time(self + i - 1, self + i)) == 0)
				continue ;
			if (!(opt & FT_LS_ASCT) &&
				(c = ls_ent_sort_alpha(self + i - 1, self + i)) == 0)
				continue ;
			if ((opt & FT_LS_REVE) && c > 0)
				continue ;
			if (!(opt & FT_LS_REVE) && c < 0)
				continue ;
			tmp = self[i - 1];
			self[i - 1] = self[i];
			self[i] = tmp;
		}
}
