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

inline uint8_t	ls_entry_ctor(t_ls_entry *self, char *path, t_bool r)
{
	FT_INIT(self, t_ls_entry);
	if (!path || lstat(path, &self->stat) < 0)
		return (1);
	else if (r && S_ISDIR(self->stat.st_mode) && !(self->dir = opendir(path)))
		return (1);
	self->path = path;
	return (0);
}

inline void		ls_entry_dtor(t_ls_entry *self)
{
	if (self->dir)
		(void)(closedir(self->dir) & (size_t)(self->dir = NULL));
	if (self->path)
	{
		free(self->path);
		self->path = NULL;
	}
}

static void		ls_ent_printl(struct stat *s, uint8_t md)
{
	ls_print_dtype(s->st_mode);
	ls_print_rights(s->st_mode);
	(void)(ft_putc(1, ' ') & ft_putn(1, s->st_nlink, 10) & ft_putc(1, ' '));
	ls_print_gps(s, getpwuid(s->st_uid), getgrgid(s->st_gid));
	if (S_ISCHR(s->st_mode) || S_ISBLK(s->st_mode))
		(void)(ft_putn(1, (s->st_rdev >> 24) & 0xFF, 10) & ft_puts(1, ", ") &
		ft_putn(1, s->st_rdev & 0xFFFFFF, 10));
	else
		(void)(ft_putr(1, ' ', md - ft_intlen(s->st_size, 10)) &
		ft_putn(1, s->st_size, 10));
	ls_print_about(s);
}

static void		ls_ent_print1(t_ls_entry *self, uint8_t maxd, uint8_t opt)
{
	if (opt & LS_LONG)
		ls_ent_printl(&self->stat, maxd);
	ft_puts(1, ft_basename(self->path));
	if (opt & LS_LONG && S_ISLNK(self->stat.st_mode))
		ls_print_linkto(self->path);
}

inline void		ls_entry_print(t_ls_entry *self, size_t n, uint8_t opt)
{
	size_t		i;
	size_t		s[3];

	ft_memset(s, 0, 3 * sizeof(size_t));
	if ((opt & LS_LONG) != (i = 0))
		while (i < n)
		{
			s[0] += (self + i)->stat.st_blocks;
			s[2] = ft_intlen((self + i++)->stat.st_size, 10);
			s[1] = MAX(s[1], s[2]);
		}
	ls_entry_sort(self, n, opt);
	if ((opt & LS_LONG) != (i = 0))
		(void)(ft_puts(1, "total ") & ft_putn(1, s[0], 10) & ft_putc(1, '\n'));
	while (i < n)
	{
		ls_ent_print1(self + i++, (uint8_t)s[1], opt);
		if (opt & LS_LONG)
			ft_putc(1, '\n');
		else if (i < n)
			ft_puts(1, "  ");
	}
	if (n && !(opt & LS_LONG))
		ft_putc(1, '\n');
}
