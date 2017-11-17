/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls/ctx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:57:53 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CTX_H
# define LS_CTX_H

# include <stdio.h>

# include "opt.h"
# include "ent.h"

typedef	struct	s_ls_ctx
{
	char		*prg;
	uint8_t		opts;
	t_vstr		paths;
	t_vec		entries;
}				t_ls_ctx;

extern uint8_t	ls_ctor(t_ls_ctx *self, int ac, char **av);
extern void		ls_dtor(t_ls_ctx *self);
extern uint8_t	ls_usage(t_ls_ctx *ctx, char opt);
extern uint8_t	ls_errno(t_ls_ctx *ctx, char *dir);

#endif
