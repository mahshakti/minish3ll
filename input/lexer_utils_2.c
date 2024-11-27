/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesumore <jesumore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:58 by jesumore          #+#    #+#             */
/*   Updated: 2024/11/25 17:07:16 by jesumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_to_dllist_check(t_shell *shell)
{
	replace_with_envp(shell);
	if (split_tokens(shell, (char *)shell->input) == 1)
	{
		print_error(1, shell, ERR_FIRST_QUOTE, 0);
		return (1);
	}
	if (!shell->token_list || !shell->token_list->data)
	{
		print_error(1, shell, ERR_TOKEN, 0);
		return (1);
	}
	return (0);
}
