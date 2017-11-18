/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 11:43:54 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls/ctx.h"

inline uint8_t	ls_ctor(t_ls_ctx *self, int ac, char **av)
{
	int		i;

	i = 0;
	ft_vec_ctor(&self->entries, sizeof(t_ls_ent));
	while (++i < ac)
		if (*av[i] != '-' && !ft_vstr_pushc(&self->paths, av[i]))
			return (1);
		else if (*av[i] == '-' && ls_opt_ctor(&self->opts, av[i]))
			return (ls_usage(self, *++av[i]));
	return (0);
}

inline void		ls_dtor(t_ls_ctx *self)
{
	ft_vstr_dtor(&self->paths, NULL);
	ft_vec_dtor(&self->entries, (void (*)(void *))ls_ent_dtor);
}

inline uint8_t	ls_usage(t_ls_ctx *ctx, char opt)
{
	ft_puts(1, ctx->prg);
	ft_puts(1, ": illegal option -- ");
	ft_putc(1, opt);
	ft_puts(1, "\nusage: ");
	ft_puts(1, ctx->prg);
	ft_putl(1, " [-Ralrt] [file ...]");
	return (EXIT_FAILURE);
}

static void		ls_pdir(t_ls_ctx *ctx, t_vec *childs, t_ls_ent *ent, size_t i)
{
	t_ls_ent		child;
	struct dirent	*de;

	childs->len = 0;
	while ((de = readdir(ent->dir)))
	{
		if (ft_isdots(de->d_name) && !(ctx->opts & FT_LS_DOTS))
			continue ;
		if (ls_ent_ctor(&child, ft_pathjoin(ent->path, de->d_name)))
			continue ;
		if ((ctx->opts & FT_LS_RECU) && !ft_isdots(de->d_name) &&
			S_ISDIR(child.stat.st_mode))
			ft_vec_putc(&ctx->entries, i, &child);
		ft_vec_pushc(childs, &child);
	}
	closedir(ent->dir);
	ent->dir = NULL;
	ls_ents_sort(childs->buf, childs->len, ctx->opts);
	if (ctx->has_errs || ctx->entries.len > 1 || (ctx->opts & FT_LS_RECU))
		(void)(ft_puts(1, ent->path) & ft_putl(1, ":"));
	ls_ents_write(childs->buf, childs->len, ctx->opts);
	if (i < ctx->entries.len)
		ft_putc(1, '\n');
}

uint8_t			ls_process(t_ls_ctx *ctx)
{
	size_t		i;
	size_t		j;
	t_ls_ent	*ent;
	t_vec		childs;

	ft_vec_ctor(&childs, sizeof(t_ls_ent));
	ls_ents_sort(ctx->entries.buf, ctx->entries.len, ctx->opts);
	i = 0;
	while (i < ctx->entries.len && (ent = (t_ls_ent *)ctx->entries.buf + i++))
		if (!S_ISDIR(ent->stat.st_mode))
			ls_ents_write(ent, 1, ctx->opts);
		else
		{
			childs.len = 0;
			ls_pdir(ctx, &childs, ent, i);
			j = 0;
			while (j < childs.len && (ent = (t_ls_ent *)childs.buf + j++))
				if (!(ctx->opts & FT_LS_RECU) || !S_ISDIR(ent->stat.st_mode))
					ls_ent_dtor(ent);
		}
	ft_vec_dtor(&childs, NULL);
	return (0);
}
