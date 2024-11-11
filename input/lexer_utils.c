/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:50:55 by csubires          #+#    #+#             */
/*   Updated: 2024/11/11 10:10:58 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_dllist	*create_token(t_shell *shell, char *str)
{
	t_dllist	*node;

	node = dlist_new(str);
	if (!node)
		dlist_clear(&shell->token_list, free_data);
	return (node);
}

void	token_to_dllist(t_shell *shell, int start, int end)
{
	t_dllist	*node;
	char		*token_str;

	token_str = ft_substr(shell->input, start, end - start);
	node = create_token(shell, token_str);
	dlist_add_after(&(shell->token_list), node);
}

void	set_redirect(t_shell *shell, char *input, int *x)
{
	if (!*input)
		return ;
	if (input[*x] == '|')
	{
		token_to_dllist(shell, *x, *x + 1);
		(*x)++;
	}
	else if (input[*x] == '<' || input[*x] == '>')
	{
		if (input[*x] == input[*x + 1])
		{
			token_to_dllist(shell, *x, *x + 2);
			*x += 2;
		}
		else
		{
			token_to_dllist(shell, *x, *x + 1);
			(*x)++;
		}
	}
}

static int	isnt_metachar(char c)
{
	char	*invalid_chars;

	invalid_chars = "<>|\'\"";
	if (ft_strchr(invalid_chars, c))
		return (0);
	else if (!ft_isprint(c) || ft_isspace(c))
		return (0);
	else
		return (1);
}

void	tokenise_arg(t_shell *shell, char *input, int *x)
{
	int		start;
	int		end;

	if (isnt_metachar(input[*x]))
	{
		start = *x;
		(*x)++;
		while (isnt_metachar(input[*x]))
			(*x)++;
		end = *x;
		token_to_dllist(shell, start, end);
	}
}
