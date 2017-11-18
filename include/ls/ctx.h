/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls/ctx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 10:34:51 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CTX_H
# define LS_CTX_H

# include <stdio.h>
# include <errno.h>

# include "opt.h"
# include "ent.h"

typedef	struct	s_ls_ctx
{
	char const	*prg;
	uint8_t		opts;
	t_vstr		paths;
	t_vec		entries;
	t_bool		has_errs;
}				t_ls_ctx;

extern uint8_t	ls_ctor(t_ls_ctx *self, int ac, char **av);
extern void		ls_dtor(t_ls_ctx *self);
extern uint8_t	ls_usage(t_ls_ctx *ctx, char opt);
extern uint8_t	ls_process(t_ls_ctx *ctx);

#endif
