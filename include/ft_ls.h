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

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>

typedef enum	e_ls_opts
{
	FT_LS_DOTS = 1 << 0,
	FT_LS_LONG = 1 << 1,
	FT_LS_RECU = 1 << 2,
	FT_LS_REVE = 1 << 2,
	FT_LS_ASCT = 1 << 3
}				t_ls_opts;

typedef	struct	s_ls_ctx
{
	char		*prg;
	uint8_t		opts;
	t_vstr		files;
}				t_ls_ctx;

#endif
