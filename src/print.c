/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:32:46 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

inline void		ls_print_dtype(mode_t mode)
{
	if (S_ISBLK(mode))
		ft_putc(1, 'b');
	else if (S_ISCHR(mode))
		ft_putc(1, 'c');
	else if (S_ISDIR(mode))
		ft_putc(1, 'd');
	else if (S_ISLNK(mode))
		ft_putc(1, 'l');
	else if (S_ISSOCK(mode))
		ft_putc(1, 's');
	else if (S_ISFIFO(mode))
		ft_putc(1, 'p');
	else
		ft_putc(1, '-');
}

inline void		ls_print_rights(mode_t mode)
{
	ft_putc(1, (char)(mode & S_IRUSR ? 'r' : '-'));
	ft_putc(1, (char)(mode & S_IWUSR ? 'w' : '-'));
	if (mode & S_IXUSR)
		ft_putc(1, (char)(mode & S_ISUID ? 's' : 'x'));
	else
		ft_putc(1, (char)(mode & S_ISUID ? 'S' : '-'));
	ft_putc(1, (char)(mode & S_IRGRP ? 'r' : '-'));
	ft_putc(1, (char)(mode & S_IWGRP ? 'w' : '-'));
	if (mode & S_IXGRP)
		ft_putc(1, (char)(mode & S_ISGID ? 's' : 'x'));
	else
		ft_putc(1, (char)(mode & S_ISGID ? 'S' : '-'));
	ft_putc(1, (char)(mode & S_IROTH ? 'r' : '-'));
	ft_putc(1, (char)(mode & S_IWOTH ? 'w' : '-'));
	if (mode & S_IXOTH)
		ft_putc(1, (char)(mode & S_ISVTX ? 't' : 'x'));
	else
		ft_putc(1, (char)(mode & S_ISVTX ? 'T' : '-'));
	ft_putc(1, ' ');
}

inline void		ls_print_gps(t_ls_entry *self, uint8_t pad[2])
{
	if (self->usr)
		ft_padl(1, self->usr->pw_name, pad[0]);
	else
		ft_padnl(1, self->stat.st_uid, 10, pad[0]);
	ft_putc(1, ' ');
	ft_putc(1, ' ');
	if (self->grp)
		ft_padl(1, self->grp->gr_name, pad[1]);
	else
		ft_padnl(1, self->stat.st_gid, 10, pad[1]);
	ft_putc(1, ' ');
}

inline void		ls_print_about(struct stat *stat)
{
	time_t		now;
	time_t		mtime;
	time_t		diff;
	char		*tstr;

	now = time(NULL);
	mtime = stat->st_mtime;
	tstr = ctime(&mtime);
	diff = now - mtime;
	(void)(ft_putc(1, ' ') & write(1, &(tstr[4]), 6) & ft_putc(1, ' '));
	if (diff < 0)
		(void)(ft_putc(1, ' ') & write(1, &(tstr[24]), 5));
	else if (diff < (-3600 * 24 * 30.5 * 6) || diff > (3600 * 24 * 30.5 * 6))
		(void)(ft_putc(1, ' ') & write(1, &(tstr[20]), 4));
	else
		write(1, &(tstr[11]), 5);
	ft_putc(1, ' ');
}
