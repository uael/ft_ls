/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls/opt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:55:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_OPT_H
# define LS_OPT_H

# include <libft.h>
# include <dirent.h>

typedef enum	e_ls_opts
{
	FT_LS_DOTS = 1 << 0,
	FT_LS_LONG = 1 << 1,
	FT_LS_RECU = 1 << 2,
	FT_LS_REVE = 1 << 2,
	FT_LS_ASCT = 1 << 3
}				t_ls_opts;

extern uint8_t	ls_opt_ctor(uint8_t *self, char *s);

#endif
