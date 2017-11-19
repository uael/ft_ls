/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:57 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

inline uint8_t	ls_entry_ctor(t_ls_entry *self, char *path)
{
	FT_INIT(self, t_ls_entry);
	if (!path || lstat(path, &self->stat) < 0)
		return (1);
	self->path = path;
	return (0);
}

inline void		ls_entry_dtor(t_ls_entry *self)
{
	if (self->path)
	{
		free(self->path);
		self->path = NULL;
	}
}

static void		ls_ent_printl(t_ls_entry *self, uint8_t pad[4])
{
	ls_print_dtype(self->stat.st_mode);
	ls_print_rights(self->stat.st_mode);
 	(void)(ft_putc(1, ' ') & ft_padnr(1, self->stat.st_nlink, 10, pad[0])
		& ft_putc(1, ' '));
	ls_print_gps(self, pad + 1);
	if (S_ISCHR(self->stat.st_mode) || S_ISBLK(self->stat.st_mode))
		(void)(ft_putn(1, (self->stat.st_rdev >> 24) & 0xFF, 10) &
		ft_puts(1, ", ") & ft_putn(1, self->stat.st_rdev & 0xFFFFFF, 10));
	else
		ft_padnr(1, self->stat.st_size, 10, pad[3]);
	ls_print_about(&self->stat);
}

static void		ls_ent_print1(t_ls_entry *self, uint8_t pad[4], uint8_t opt)
{
	if (opt & LS_LONG)
		ls_ent_printl(self, pad);
	ft_puts(1, ft_basename(self->path));
	if (opt & LS_LONG && S_ISLNK(self->stat.st_mode))
		ls_print_linkto(self->path);
	ft_putc(1, (char)((opt & LS_LONG) ? '\n' : ' '));
}

inline void		ls_entry_print(t_ls_entry *self, size_t n, uint8_t opt)
{
	size_t		i;
	uint8_t		p[4];
	size_t		t;

	ft_memset(p, (int)(t = 0), 4 * sizeof(uint8_t));
	if ((opt & LS_LONG) != (i = 0))
		while (i < n)
		{
			t += (self + i)->stat.st_blocks;
			p[0] = ft_u8max(p[0], ft_intlen((self + i)->stat.st_nlink, 10));
			if (((self + i)->usr = getpwuid((self + i)->stat.st_uid)))
				p[1] = ft_u8max(p[1], (uint8_t)ft_strlen(self->usr->pw_name));
			else
				p[1] = ft_u8max(p[1], ft_intlen((self + i)->stat.st_uid, 10));
			if (((self + i)->grp = getgrgid((self + i)->stat.st_gid)))
				p[2] = ft_u8max(p[2], (uint8_t)ft_strlen(self->grp->gr_name));
			p[3] = ft_u8max(p[3], ft_intlen((self + i++)->stat.st_size, 10));
		}
	ls_entry_sort(self, n, opt);
	if ((opt & LS_LONG) != (i = 0))
		(void)(ft_puts(1, "total ") & ft_putu(1, t, 10) & ft_putc(1, '\n'));
	while (i < n)
		ls_ent_print1(self + i++, (uint8_t *)p, opt);
	if (n && !(opt & LS_LONG))
		ft_putc(1, '\n');
}
