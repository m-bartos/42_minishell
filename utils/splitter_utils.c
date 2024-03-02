/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:10:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/02 14:55:33 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if (c == 9 || c == 10 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_end_of_word(char c)
{
	if (is_whitespace(c) || is_quote(c) || is_token(c) || c == '\0')
		return (1);
	return (0);
}

size_t	word_length(char *str)
{
	size_t	count;

	count = 0;
	while (!is_end_of_word(str[count]))
		count++;
	return (count);
}
