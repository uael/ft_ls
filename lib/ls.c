/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:27 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static uint8_t	ls_err(char const *prg, char const *arg)
{
	ft_puts(1, prg);
	ft_puts(1, ": ");
	ft_puts(1, arg);
	ft_puts(1, ": ");
	ft_putl(1, strerror(errno));
	return (1);
}

inline uint8_t	ls_ctor(t_ls *self, int ac, char **av)
{
	int			i;
	t_ls_entry	ent;
	char		c;

	ft_memset(self, i = 0, sizeof(t_ls));
	self->prg = ft_basename(av[0]);
	ft_vec_ctor(&self->entries, sizeof(t_ls_entry));
	while (++i < ac)
		if (*av[i] != '-' && ls_entry_ctor(&ent, av[i]))
			ls_err(self->prg, av[i]);
		else if (*av[i] != '-' && !(ent.path = ft_strdup(ent.path)))
			return (1);
		else if (*av[i] != '-' && !ft_vec_pushc(&self->entries, &ent))
			return (1);
		else if (*av[i] == '-' && ls_opt_parse(&self->opt, av[i], &c))
			return ((uint8_t)((ft_puts(1, ft_basename(av[0])) &
			ft_puts(1, ": illegal option -- ") & ft_putc(1, c) &
			ft_puts(1, "\nusage: ") & ft_puts(1, ft_basename(av[0])) &
			ft_putl(1, " [-Ralrt] [file ...]")) > 0));
	if (!ft_vec_size(&self->entries) && (ls_entry_ctor(&ent, ft_strdup("."))
		|| !ft_vec_pushc(&self->entries, &ent)))
		return (1);
	return (0);
}

inline void		ls_dtor(t_ls *self)
{
	ft_vec_dtor(&self->entries, (void (*)(void *)) ls_entry_dtor);
}

static t_bool	ls_childs(t_ls *self, t_vec *v, t_ls_entry *ent, size_t i)
{
	t_ls_entry		e;
	struct dirent	*de;
	size_t			j;

	v->len = 0;
	if (!(ent->dir = opendir(ent->path)))
		return ((t_bool)!ls_err(self->prg, ft_basename(ent->path)));
	j = 0;
	while ((de = readdir(ent->dir)))
	{
		if (ft_isdots(de->d_name) && !(self->opt & LS_DOTS))
			continue ;
		if (ls_entry_ctor(&e, ft_pathjoin(ent->path, de->d_name)))
			continue ;
		if ((self->opt & LS_RECU) && !ft_isdots(de->d_name) &&
			S_ISDIR(e.stat.st_mode) && ++j)
			ft_vec_putc(&self->entries, i, &e);
		ft_vec_pushc(v, &e);
	}
	(void)(closedir(ent->dir) & (size_t)(ent->dir = NULL));
	if (j)
		ls_entry_sort((t_ls_entry *) self->entries.buf + i, j, self->opt);
	return ((t_bool)(v->len > 0));
}

inline void		ls_run(t_ls *self)
{
	size_t		i;
	size_t		j;
	t_ls_entry	*e;
	t_vec		v;

	ft_vec_ctor(&v, sizeof(t_ls_entry));
	ls_entry_sort(self->entries.buf, self->entries.len, self->opt);
	i = 0;
	while (i < self->entries.len && (e = (t_ls_entry *)self->entries.buf + i++))
		if (!S_ISDIR(e->stat.st_mode))
			ls_entry_print(e, 1, self->opt);
		else
		{
			if (self->errs || self->entries.len > 1 || (self->opt & LS_RECU))
				(void)(ft_puts(1, e->path) & ft_putl(1, ":"));
			if (!ls_childs(self, &v, e, i) &&
				(i < self->entries.len ? ft_putc(1, '\n') : 1))
				continue ;
			ls_entry_print(v.buf, v.len, self->opt);
			j = (i < self->entries.len ? (size_t)(ft_putc(1, '\n') & 0) : 0);
			while (j < v.len && (e = (t_ls_entry *)v.buf + j++))
				if (!(self->opt & LS_RECU) || !S_ISDIR(e->stat.st_mode))
					ls_entry_dtor(e);
		}
	ft_vec_dtor(&v, NULL);
}
