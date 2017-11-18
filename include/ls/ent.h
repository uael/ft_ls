/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls/ent.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 10:28:10 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_ENT_H
# define LS_ENT_H

# include <libft.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "opt.h"

typedef struct	s_ls_ent
{
	char		*path;
	DIR			*dir;
	struct stat	stat;
}				t_ls_ent;

extern uint8_t	ls_ent_ctor(t_ls_ent *self, char *path);
extern void		ls_ent_dtor(t_ls_ent *self);
extern void		ls_ents_sort(t_ls_ent *ents, size_t n, uint8_t opt);
extern void		ls_ents_write(t_ls_ent *ents, size_t n, uint8_t opt);

#endif
