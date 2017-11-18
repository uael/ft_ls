/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 18:58:53 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENT_H
# define ENT_H

# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "ls.h"

typedef enum	e_ls_opts
{
	FT_LS_DOTS = 1 << 0,
	FT_LS_LONG = 1 << 1,
	FT_LS_RECU = 1 << 2,
	FT_LS_REVE = 1 << 3,
	FT_LS_ASCT = 1 << 4
}				t_ls_opts;

typedef struct	s_ls_ent
{
	char			*path;
	DIR				*dir;
	struct stat		stat;
}				t_ls_ent;

extern uint8_t	ls_ent_ctor(t_ls_ent *self, char *path, t_bool root);
extern void		ls_ent_dtor(t_ls_ent *self);
extern void		ls_ent_sort(t_ls_ent *self, size_t n, uint8_t opt);
extern void		ls_ent_print(t_ls_ent *self, size_t n, uint8_t opt);

#endif
