/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 16:56:15 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <libft.h>

typedef	struct	s_ls_ctx
{
	uint8_t		opt;
	t_vec		ents;
	t_bool		has_errs;
}				t_ls_ctx;

extern uint8_t	ls_ctor(t_ls_ctx *self, int ac, char **av);
extern void		ls_dtor(t_ls_ctx *self);
extern void		ls_run(t_ls_ctx *c);

#endif
