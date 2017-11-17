/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 12:56:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls/opt.h"

inline uint8_t	ls_opt_ctor(uint8_t *self, char *s)
{
	while (*++s)
		if (*s == 'a')
			*self |= FT_LS_DOTS;
		else if (*s == 'l')
			*self |= FT_LS_LONG;
		else if (*s == 'R')
			*self |= FT_LS_RECU;
		else if (*s == 'r')
			*self |= FT_LS_REVE;
		else if (*s == 't')
			*self |= FT_LS_ASCT;
		else if (*s)
			return (1);
	return (0);
}
