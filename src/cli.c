/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 11:02:24 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static uint8_t	ls_errno(t_ls_ctx *ctx, char *dir)
{
	ft_puts(1, ctx->prg);
	ft_puts(1, ": cannot access '");
	ft_puts(1, dir);
	ft_puts(1, "': ");
	ft_putl(1, strerror(errno));
	return (EXIT_FAILURE);
}

int				main(int ac, char **av)
{
	t_ls_ctx	ctx;
	t_ls_ent	ent;
	char		**path;

	FT_INIT(&ctx, t_ls_ctx);
	ctx.prg = ft_basename(av[0]);
	if (ls_ctor(&ctx, ac, av))
		return (EXIT_FAILURE);
	if (!ft_vstr_size(&ctx.paths) && !ft_vstr_pushc(&ctx.paths, "."))
		return (EXIT_FAILURE);
	path = ft_vstr_begin(&ctx.paths) - 1;
	while (++path != ft_vstr_end(&ctx.paths))
		if (ls_ent_ctor(&ent, ft_strdup(*path)))
			ctx.has_errs += ls_errno(&ctx, *path);
		else
			ft_vec_pushc(&ctx.entries, &ent);
	if (ls_process(&ctx))
		return (EXIT_FAILURE);
	ls_dtor(&ctx);
	return (EXIT_SUCCESS);
}
