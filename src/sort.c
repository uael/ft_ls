/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 17:53:34 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls/ent.h"

void	ls_ents_sort(t_ls_ent *ents, size_t n, uint8_t opt)
{
	size_t		i;
	size_t		j;
	t_ls_ent	tmp;

	(void) opt;
	j = 0;
	while (j < n - 1)
	{
		i = 0;
		while (i < n - 1)
		{
			if (ft_strcmp(ents[i].path, ents[i + 1].path) > 0)
			{
				tmp = ents[i];
				ents[i] = ents[i + 1];
				ents[i + 1] = tmp;
			}
			++i;
		}
		++j;
	}
}
