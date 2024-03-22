/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:10:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/21 11:33:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

size_t	count_word_length(char *str)
{
	char	quotes_type;
	size_t	size;
	int		inside_quotes;

	inside_quotes = 0;
	size = 0;
	while (str[size])
	{
		if (inside_quotes == 0 && is_quote(str[size]))
		{
			quotes_type = str[size];
			inside_quotes = 1;
		}
		else if (inside_quotes == 1 && str[size] == quotes_type)
			inside_quotes = 0;
		else if (inside_quotes == 0 && is_whitespace(str[size]))
			break ;
		else if (inside_quotes == 0 && is_operator(str[size]))
			break ;
		size++;
	}
	return (size);
}
