/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:44:58 by jesumore          #+#    #+#             */
/*   Updated: 2024/11/28 22:15:55 by csubires         ###   ########.fr       */
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

void	replace_value(t_shell *shell, int *x, char *key, char *value)
{
	char	*tmp_str;
	int		len;

	len = ft_strlen(value);
	tmp_str = ft_strreplace(shell->input, *x, \
	(ft_strlen(key) + *x + 1), value);
	free(shell->input);
	shell->input = tmp_str;
	if (key && key[0] == '?')
	{
		free(value);
		value = 0;
	}
	if (key)
	{
		free(key);
		key = 0;
	}
	*x += len;
}
