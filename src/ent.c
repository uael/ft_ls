/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 11:13:24 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls/ent.h"

inline uint8_t	ls_ent_ctor(t_ls_ent *self, char *path)
{
	FT_INIT(self, t_ls_ent);
	if (!path)
		return (1);
	if (lstat(path, &self->stat) < 0)
		return (1);
	else if (S_ISDIR(self->stat.st_mode) && !(self->dir = opendir(path)))
		return (1);
	self->path = path;
	return (0);
}

inline void		ls_ent_dtor(t_ls_ent *self)
{
	if (S_ISDIR(self->stat.st_mode) && self->dir)
	{
		closedir(self->dir);
		self->dir = NULL;
	}
	free(self->path);
}

static void		ls_ent_write(t_ls_ent *self, uint8_t opt)
{
	(void)opt;
	ft_puts(1, ft_basename(self->path));
}

void			ls_ents_write(t_ls_ent *ents, size_t n, uint8_t opt)
{
	size_t		i;

	if (opt & FT_LS_LONG)
		(void)(ft_puts(1, "total ") & ft_putn(1, n, 10) & ft_putc(1, '\n'));
	i = 0;
	while (i < n)
	{
		ls_ent_write(ents + i++, opt);
		if (opt & FT_LS_LONG)
			ft_putc(1, '\n');
		else if (i < n)
			ft_puts(1, "  ");
	}
	if (n && !(opt & FT_LS_LONG))
		ft_putc(1, '\n');
}
