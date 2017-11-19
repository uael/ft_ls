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

static uint8_t	ls_entry_strsize(t_ls_entry *self)
{
	char	unit;
	uint8_t	i;
	float	f;

	if (S_ISCHR(self->stat.st_mode) || S_ISBLK(self->stat.st_mode))
	{
		i = ft_intstr(self->strsz, (self->stat.st_rdev >> 24) & 0xFF, 10);
		i += ((int64_t)ft_strcpy(self->strsz + i, ", ") & 0) + 2;
		i += ft_intstr(self->strsz + i, self->stat.st_rdev & 0xFFFFFF, 10);
	}
	else
	{
		f = ls_fmt_size(self->stat.st_size, &unit);
		if (f < 10)
			i = ft_floatstr(self->strsz, f, 10, 10);
		else
			i = ft_intstr(self->strsz,
						  (int64_t)f + (f - (int64_t)f >= 0.5 ? 1 : 0), 10);
		self->strsz[i++] = unit;
	}
	self->strsz[i] = '\0';
	return (i);
}

static void		ls_ent_printone(t_ls_entry *self, uint8_t *pad, uint8_t opt)
{
	char	cp[PATH_MAX];
	ssize_t	sz;

	if (opt & LS_LONG)
	{
		ls_print_dtype(self->stat.st_mode);
		ls_print_rights(self->stat.st_mode);
		(void)(ft_putc(1, ' ') & ft_padnr(1, self->stat.st_nlink, 10, pad[0])
			   & ft_putc(1, ' '));
		ls_print_gps(self, pad + 1);
		ft_putc(1, ' ');
		ft_padr(1, self->strsz, pad[3]);
		ls_print_about(&self->stat);
	}
	ft_puts(1, ft_basename(self->path));
	if (opt & LS_LONG && S_ISLNK(self->stat.st_mode))
	{
		ft_strcpy(cp, self->path);
		if ((sz = readlink(self->path, cp, PATH_MAX)) > 0)
			(void)((cp[sz] = '\0') & ft_puts(1, " -> ") & ft_puts(1, cp));
	}
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
			p[1] = ((self + i)->usr = getpwuid((self + i)->stat.st_uid))
				? ft_u8max(p[1], (uint8_t)ft_strlen((self + i)->usr->pw_name))
				: ft_u8max(p[1], ft_intlen(self->stat.st_uid, 10));
			p[2] = ((self + i)->grp = getgrgid((self + i)->stat.st_gid))
				? ft_u8max(p[1], (uint8_t)ft_strlen((self + i)->grp->gr_name))
				: ft_u8max(p[1], ft_intlen(self->stat.st_gid, 10));
			p[3] = ft_u8max(p[2], ls_entry_strsize(self + i++));
		}
	ls_entry_sort(self, n, opt);
	if ((opt & LS_LONG) != (i = 0) && t > 0)
		(void)(ft_puts(1, "total ") & ft_putu(1, t, 10) & ft_putc(1, '\n'));
	while (i < n)
		ls_ent_printone(self + i++, (uint8_t *) p, opt);
	if (n && !(opt & LS_LONG))
		ft_putc(1, '\n');
}
