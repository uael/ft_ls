/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 19:00:39 by null             ###   ########.fr       */
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
		if (ls_ent_ctor(&ent, *path))
			ls_errno(&ctx, *path);
		else
			ft_vec_pushc(&ctx.entries, &ent);
	if (!ft_vec_size(&ctx.entries) && !ls_ent_ctor(&ent, "."))
		ft_vec_pushc(&ctx.entries, &ent);
	if (ls_process(&ctx))
		return (EXIT_FAILURE);
	ls_dtor(&ctx);
	ft_putc(1, '\n');
	return (EXIT_SUCCESS);
}
