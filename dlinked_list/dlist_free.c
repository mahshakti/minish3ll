/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:24:39 by csubires          #+#    #+#             */
/*   Updated: 2024/10/14 07:53:30 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinked_list.h"

void	dlist_free(void **node)
{
	if (node && *node)
	{
		free(*node);
		*node = 0;
	}
}
