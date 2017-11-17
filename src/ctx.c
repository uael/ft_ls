/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 13:03:06 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls/ctx.h"

uint8_t	ls_ctor(t_ls_ctx *self, int ac, char **av)
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
	ft_vec_dtor(&self->entries, (void (*)(void *))ls_ent_dtor);
}

uint8_t	ls_usage(t_ls_ctx *ctx, char opt)
{
	ft_puts(2, ctx->prg);
	ft_puts(2, ": illegal option -- ");
	ft_putc(2, opt);
	ft_puts(2, "\nusage: ");
	ft_puts(2, ctx->prg);
	ft_putl(2, " [-Ralrt] [file ...]");
	return (EXIT_FAILURE);
}

uint8_t	ls_errno(t_ls_ctx *ctx, char *dir)
{
	ft_puts(2, ctx->prg);
	ft_puts(2, ": cannot access '");
	ft_puts(2, dir);
	perror("'");
	return (EXIT_FAILURE);
}
