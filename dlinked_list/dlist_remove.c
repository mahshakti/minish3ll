/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:04:22 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 07:49:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

void	dlist_remove(t_dllist **dllist, t_dllist *node, void (*del)(void*))
{
	if (dllist && *dllist && node && dlist_has(*dllist, node))
	{
		if (node == *dllist)
			dlist_remove_before(dllist, del);
		node->prev->next = node->next;
		del(node->data);
		free(node);
		node = 0;
	}
}
