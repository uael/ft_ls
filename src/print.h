/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:14:58 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LONG_H
# define LONG_H

# include <pwd.h>
# include <grp.h>

# include "ent.h"

extern void	ls_print_dtype(mode_t mode);
extern void	ls_print_rights(mode_t mode);
extern void	ls_print_gps(struct stat *s, struct passwd *u, struct group *g);
extern void	ls_print_about(struct stat *stat);
extern void	ls_print_linkto(char *p);

#endif
