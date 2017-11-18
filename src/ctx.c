/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:00:39 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ent.h"

static uint8_t	ls_opt_parse(uint8_t *self, char *s, char *c)
{
	while (*++s)
		if ((*c = *s) == 'a')
			*self |= FT_LS_DOTS;
		else if (*s == 'l')
			*self |= FT_LS_LONG;
		else if (*s == 'R')
			*self |= FT_LS_RECU;
		else if (*s == 'r')
			*self |= FT_LS_REVE;
		else if (*s == 't')
			*self |= FT_LS_ASCT;
		else if (*s)
			return (1);
	return (0);
}

inline uint8_t	ls_ctor(t_ls_ctx *self, int ac, char **av)
{
	int			i;
	t_ls_ent	ent;
	char		c;

	ft_memset(self, i = 0, sizeof(t_ls_ctx));
	ft_vec_ctor(&self->ents, sizeof(t_ls_ent));
	while (++i < ac)
		if (*av[i] != '-' && ls_ent_ctor(&ent, av[i], 1))
			(void)(ft_puts(1, ft_basename(av[0])) &
			ft_puts(1, ": cannot access '") &
			ft_puts(1, av[i]) & ft_puts(1, "': ") &
			ft_putl(1, strerror(errno)));
		else if (*av[i] != '-' && !(ent.path = ft_strdup(ent.path)))
			return (1);
		else if (*av[i] != '-' && !ft_vec_pushc(&self->ents, &ent))
			return (1);
		else if (*av[i] == '-' && ls_opt_parse(&self->opt, av[i], &c))
			return ((uint8_t)((ft_puts(1, ft_basename(av[0])) &
			ft_puts(1, ": illegal option -- ") & ft_putc(1, c) &
			ft_puts(1, "\nusage: ") & ft_puts(1, ft_basename(av[0])) &
			ft_putl(1, " [-Ralrt] [file ...]")) > 0));
	if (!ft_vec_size(&self->ents) && (ls_ent_ctor(&ent, ft_strdup("."), 1)
		|| !ft_vec_pushc(&self->ents, &ent)))
		return (1);
	return (0);
}

inline void		ls_dtor(t_ls_ctx *self)
{
	ft_vec_dtor(&self->ents, (void (*)(void *))ls_ent_dtor);
}

static t_bool	ls_childs(t_ls_ctx *c, t_vec *v, t_ls_ent *ent, size_t i)
{
	t_ls_ent		e;
	struct dirent	*de;
	size_t			j;

	v->len = 0;
	ent->dir = ent->dir ? ent->dir : opendir(ent->path);
	j = 0;
	while ((de = readdir(ent->dir)))
	{
		if (ft_isdots(de->d_name) && !(c->opt & FT_LS_DOTS))
			continue ;
		if (ls_ent_ctor(&e, ft_pathjoin(ent->path, de->d_name), 0))
			continue ;
		e.dty = de->d_type;
		if ((c->opt & FT_LS_RECU) && !ft_isdots(de->d_name) &&
			S_ISDIR(e.stat.st_mode) && ++j)
			ft_vec_putc(&c->ents, i, &e);
		ft_vec_pushc(v, &e);
	}
	(void)(closedir(ent->dir) & (size_t)(ent->dir = NULL));
	(j ? ls_ent_sort((t_ls_ent *)c->ents.buf + i, j, c->opt) : (void)0);
	return ((t_bool)(v->len > 0));
}

inline void		ls_run(t_ls_ctx *c)
{
	size_t		i;
	size_t		j;
	t_ls_ent	*e;
	t_vec		v;

	ft_vec_ctor(&v, sizeof(t_ls_ent));
	ls_ent_sort(c->ents.buf, c->ents.len, c->opt);
	i = 0;
	while (i < c->ents.len && (e = (t_ls_ent *)c->ents.buf + i++))
		if (!S_ISDIR(e->stat.st_mode))
			ls_ent_print(e, 1, c->opt);
		else
		{
			if (c->has_errs || c->ents.len > 1 || (c->opt & FT_LS_RECU))
				(void)(ft_puts(1, e->path) & ft_putl(1, ":"));
			if (!ls_childs(c, &v, e, i) &&
				(i < c->ents.len ? ft_putc(1, '\n') : 1))
				continue ;
			ls_ent_print(v.buf, v.len, c->opt);
			j = (i < c->ents.len ? (size_t)(ft_putc(1, '\n') & 0) : 0);
			while (j < v.len && (e = (t_ls_ent *)v.buf + j++))
				if (!(c->opt & FT_LS_RECU) || !S_ISDIR(e->stat.st_mode))
					ls_ent_dtor(e);
		}
	ft_vec_dtor(&v, NULL);
}
