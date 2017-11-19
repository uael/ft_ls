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
	self->usr = getpwuid(self->stat.st_uid);
	self->grp = getgrgid(self->stat.st_gid);
	if (S_ISLNK(self->stat.st_mode) &&
		(self->lnl = readlink(self->path, self->ln, PATH_MAX)))
	{
		if (!(self->lns = malloc(sizeof(struct stat))))
			return (1);
		self->ln[self->lnl] = '\0';
		lstat(self->ln, self->lns);
	}
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

static void		ls_ent_dumpone(t_ls_entry *self, uint8_t *pad, uint8_t opt)
{
	char	cp[PATH_MAX];

	if (opt & LS_LONG)
	{
		ls_print_dtype(self->stat.st_mode);
		ls_print_rights(self->stat.st_mode);
		(void)(ft_putc(1, ' ') & ft_padnr(1, self->stat.st_nlink, 10, pad[0])
			& ft_putc(1, ' '));
		ls_print_gps(self, pad + 1);
		ft_putc(1, ' ');
		if (opt & LS_UNIT)
			ft_padr(1, self->strsz, pad[3] + 1);
		else
			ft_padnr(1, self->stat.st_size, 10, pad[3]);
		ls_print_about(&self->stat);
	}
	ft_puts(1, ft_basename(self->path));
	if (opt & LS_LONG && S_ISLNK(self->stat.st_mode) && self->lnl)
	{
		ft_strcpy(cp, self->ln);
		(void)((cp[self->lnl] = '\0') & ft_puts(1, " -> ") & ft_puts(1, cp));
	}
	ft_putc(1, (char)((opt & LS_LONG) || (opt & LS_LINE) ? '\n' : ' '));
}

inline void		ls_entry_dump(t_ls_entry *ent, size_t n, uint8_t opt, t_bool s)
{
	size_t		i;
	uint8_t		p[4];
	size_t		t;

	ft_memset(p, (int)(t = 0), 4 * sizeof(uint8_t));
	if ((opt & LS_LONG) != (i = 0))
		while (i < n)
		{
			t += (ent + i)->stat.st_blocks;
			p[0] = ft_u8max(p[0], ft_intlen((ent + i)->stat.st_nlink, 10));
			p[1] = ft_u8max(p[1], (ent + i)->usr ? (uint8_t)ft_strlen(
				(ent + i)->usr->pw_name) : ft_intlen(ent->stat.st_uid, 10));
			p[2] = ft_u8max(p[1], (ent + i)->grp ? (uint8_t)ft_strlen(
				(ent + i)->grp->gr_name) : ft_intlen(ent->stat.st_gid, 10));
			p[3] = ft_u8max(p[3], (opt & LS_UNIT) ? ls_entry_strsize(ent + i++)
				: ft_intlen((ent + i++)->stat.st_size, 10));
		}
	ls_entry_sort(ent, n, opt, 0);
	if ((opt & LS_LONG) != (i = 0) && s)
		(void)(ft_puts(1, "total ") & ft_putu(1, t, 10) & ft_putc(1, '\n'));
	while (i < n)
		ls_ent_dumpone(ent + i++, (uint8_t *)p, opt);
	if (n && !(opt & LS_LONG) && !(opt & LS_LINE))
		ft_putc(1, '\n');
}
