/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:39:58 by csubires          #+#    #+#             */
/*   Updated: 2024/11/25 11:15:11 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_token(t_shell *shell, char *input, int *x)
{
	int		start;
	int		end;
	char	quote;
	char	before_quote;

	if (input[*x] && (input[*x] == '\'' || input[*x] == '\"'))
	{
		if (*x == 0)
			return (1);
		else
			before_quote = input[*x - 1];
		quote = input[*x];
		start = ++(*x);
		while (input[*x] && input[*x] != quote)
			(*x)++;
		end = *x;
		token_to_dllist(shell, start, end, before_quote);
		(*x)++;
	}
	return (0);
}

static int	split_tokens(t_shell *shell, char *input)
{
	int		x;

	if (!*input)
		return (2);
	x = 0;
	while (x < (int)ft_strlen(input))
	{
		if (check_token(shell, input, &x) == 1)
			return (1);
		if (x >= (int)ft_strlen(input))
			return (2);
		set_redirect(shell, input, &x);
		if (x >= (int)ft_strlen(input))
			return (2);
		if (!ft_isprint(input[x]) || ft_isspace(input[x]))
			x++;
		else
			tokenise_arg(shell, input, &x);
	}
	return (0);
}

static void	manage_quotes(char c, int *flag)
{
	if (!*flag)
	{
		if (c == '\'')
			*flag = 1;
		else if (c == '\"')
			*flag = 2;
	}
	else if (*flag == 1 && c == '\'')
		*flag = 3;
	else if (*flag == 2 && c == '\"')
		*flag = 4;
}

static void	replace_with_envp(t_shell *shell)
{
	int		flag;
	int		x;

	x = 0;
	flag = 0;
	while (shell->input[x])
		manage_quotes(shell->input[x++], &flag);
	x = 0;
	while (shell->input[x])
	{
		if ((flag == 0 || flag == 4) && shell->input[x] == '$')
			expand_envp(shell, &x);
		else
			x++;
	}
}

void	tokens_to_dllist(t_shell *shell)
{
	char	*first_token;
	char	*last_token;

	replace_with_envp(shell);
	if (split_tokens(shell, (char *)shell->input) == 1)
	{
		print_error(1, shell, ERR_FIRST_QUOTE, 0);
		return ;
	}
	first_token = (char *)shell->token_list->data;
	if (first_token && (first_token[0] != '\"') && \
	(first_token[0] != '\'') && !isnt_metachar(first_token[0]))
	{
		print_error(1, shell, ERR_TOKEN, 0);
		return ;
	}
	last_token = (char *)(dlist_last(shell->token_list)->data);
	if (last_token && (last_token[0] != '\"') && \
	(last_token[0] != '\'') && !isnt_metachar(last_token[0]))
	{
		print_error(1, shell, ERR_TOKEN, 0);
		return ;
	}
}
