/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:01:46 by csubires          #+#    #+#             */
/*   Updated: 2024/10/15 11:18:52 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	buildin_exit(t_shell *shell)
{
	printf("%s%s%s\n", BLUE, MSG_BYE, ENDC);
	shell->exit_stat = 0;
	exit(0);
}
