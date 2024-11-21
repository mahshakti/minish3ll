/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:01:46 by csubires          #+#    #+#             */
/*   Updated: 2024/11/21 11:09:06 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	buildin_exit(t_shell *shell)
{
	(void)shell;
	// shell->exit_stat = 0;
	exit(shell->exit_stat);
}
