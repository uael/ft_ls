/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 13:11:26 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static uint8_t	ls_opt_parse(uint8_t *self, char *s)
{
	while (*++s)
		if (*s == 'a')
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

	i = 0;
	FT_INIT(self, t_ls_ctx);
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
		else if (*av[i] == '-' && ls_opt_parse(&self->opt, av[i]))
			return ((uint8_t)((ft_puts(1, ft_basename(av[0])) &
			ft_puts(1, ": illegal option -- ") & ft_putc(1, *(av[i] + 1)) &
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

static t_bool	ls_childs(t_ls_ctx *ctx, t_vec *c, t_ls_ent *ent, size_t i)
{
	t_ls_ent		e;
	struct dirent	*de;
	size_t			j;

	c->len = 0;
	if (!ent->dir)
		ent->dir = opendir(ent->path);
	j = 0;
	while ((de = readdir(ent->dir)))
	{
		if (ft_isdots(de->d_name) && !(ctx->opt & FT_LS_DOTS))
			continue ;
		if (ls_ent_ctor(&e, ft_pathjoin(ent->path, de->d_name), 0))
			continue ;
		if ((ctx->opt & FT_LS_RECU) && !ft_isdots(de->d_name) &&
			S_ISDIR(e.stat.st_mode) && ++j)
			ft_vec_putc(&ctx->ents, i, &e);
		ft_vec_pushc(c, &e);
	}
	closedir(ent->dir);
	ent->dir = NULL;
	(j ? ls_ent_sort((t_ls_ent *)ctx->ents.buf + i, j, ctx->opt) : (void)0);
	return ((t_bool)(c->len > 0));
}

inline void		ls_run(t_ls_ctx *ctx)
{
	size_t		i;
	size_t		j;
	t_ls_ent	*e;
	t_vec		c;

	ft_vec_ctor(&c, sizeof(t_ls_ent));
	ls_ent_sort(ctx->ents.buf, ctx->ents.len, ctx->opt);
	i = 0;
	while (i < ctx->ents.len && (e = (t_ls_ent *)ctx->ents.buf + i++))
		if (!S_ISDIR(e->stat.st_mode))
			ls_ent_write(e, 1, ctx->opt);
		else
		{
			if (ctx->has_errs || ctx->ents.len > 1 || (ctx->opt & FT_LS_RECU))
				(void)(ft_puts(1, e->path) & ft_putl(1, ":"));
			if (!ls_childs(ctx, &c, e, i) &&
				(i < ctx->ents.len ? ft_putc(1, '\n') : 1))
				continue ;
			ls_ent_sort(c.buf, c.len, ctx->opt);
			ls_ent_write(c.buf, c.len, ctx->opt);
			j = (i < ctx->ents.len ? (size_t)(ft_putc(1, '\n') & 0) : 0);
			while (j < c.len && (e = (t_ls_ent *)c.buf + j++))
				if (!(ctx->opt & FT_LS_RECU) || !S_ISDIR(e->stat.st_mode))
					ls_ent_dtor(e);
		}
	ft_vec_dtor(&c, NULL);
}
