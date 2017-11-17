/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 13:24:06 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		main(int ac, char **av)
{
	t_ls_ctx	ctx;
	t_ls_ent	ent;
	char		**path;

	FT_INIT(&ctx, t_ls_ctx);
	if ((ctx.prg = ft_strrchr(av[0], '/')))
		++ctx.prg;
	else
		ctx.prg = av[0];
	if (ls_ctor(&ctx, ac, av))
		return (EXIT_FAILURE);
	if (!ft_vstr_size(&ctx.paths) && !ft_vstr_pushc(&ctx.paths, "."))
		return (EXIT_FAILURE);
	path = ft_vstr_begin(&ctx.paths) - 1;
	while (++path != ft_vstr_end(&ctx.paths))
		if (ls_ent_ctor(&ent, *path) || ls_ent_write(&ent, ctx.opts))
			ls_errno(&ctx, *path);
	ls_dtor(&ctx);
	return (EXIT_SUCCESS);
}
