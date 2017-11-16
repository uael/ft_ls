/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/15 18:23:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint8_t	ls_usage(t_ls_ctx *ctx, char opt)
{
	ft_putstr(ctx->prg);
	ft_putstr(": illegal option -- ");
	ft_putchar(opt);
	ft_putchar('\n');
	ft_putstr("usage: ");
	ft_putstr(ctx->prg);
	ft_putstr(" [-Ralrt] [file ...]");
	return (1);
}

uint8_t	ls_parse_opts(t_ls_ctx *ctx, int ac, char **av)
{
	int		i;
	char	*arg;

	i = -1;
	while (++i < ac && (arg = av[i]))
		if (*arg != '-' && !ft_vstr_pushc(&ctx->files, arg))
			return (1);
		else if (*arg == '-')
			while (++*arg)
				if (*arg == 'a')
					ctx->opts |= FT_LS_DOTS;
				else if (*arg == 'l')
					ctx->opts |= FT_LS_LONG;
				else if (*arg == 'R')
					ctx->opts |= FT_LS_RECU;
				else if (*arg == 'r')
					ctx->opts |= FT_LS_REVE;
				else if (*arg == 't')
					ctx->opts = FT_LS_ASCT;
				else if (*arg)
					return (ls_usage(ctx, *arg));
	return (0);
}

int		main(int ac, char **av)
{
	t_ls_ctx ctx;

	FT_INIT(&ctx, t_ls_ctx);
	if ((ctx.prg = ft_strrchr(av[0], '/')))
		++ctx.prg;
	else
		ctx.prg = av[0];
	if (ls_parse_opts(&ctx, ac, av))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
