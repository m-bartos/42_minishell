/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:47:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/15 08:40:30 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Extracts redirections (<, <<, >, >>) from a string.
 * 
 * This function takes a string, an index, and a redirection type as input.
 * It creates a new string containing the redirection symbol(s) 
 * at the beginning of the original string.
 * The size of the new string is determined based on the redirection type.
 * The index is updated to reflect the number of characters processed.
 * 
 * @param str The original string.
 * @param index A pointer to the index variable.
 * @param redir_type The type of redirection symbol.
 * @return A new string containing the redirection symbol(s),
 *         or NULL if memory allocation fails.
 */
char	*handle_redirections(char *str, size_t *index, char redir_type)
{
	size_t	size_to_malloc;
	size_t	j;
	char	*str_out;

	if (str[1] == redir_type)
		size_to_malloc = 2;
	else
		size_to_malloc = 1;
	str_out = (char *) malloc(sizeof(char) * (size_to_malloc + 1));
	if (!str_out)
		return (NULL);
	j = 0;
	while (j < size_to_malloc)
	{
		str_out[j] = str[j];
		j++;
	}
	str_out[j] = '\0';
	*index = *index + size_to_malloc;
	return (str_out);
}

/**
 * @brief Extracts the pipe character from a string.
 *
 * This function takes a string and an index as input and returns a new string
 * containing the pipe character at the start of string. It also increments
 * the index by 1.
 *
 * @param str The input string.
 * @param index A pointer to the current index.
 * @return A new string containing the pipe character,
 *         or NULL if memory allocation fails.
 */
char	*handle_pipe(char *str, size_t *index)
{
	char	*str_out;

	str_out = (char *) malloc(sizeof(char) * 2);
	if (!str_out)
		return (NULL);
	str_out[0] = str[0];
	str_out[1] = '\0';
	*index = *index + 1;
	return (str_out);
}

size_t	count_word_length(char *str)
{
	char	quotes_type;
	size_t	size;
	int		inside_quotes;

	inside_quotes = 0;
	size = 0;
	while(str[size])
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
	return(size);
}

char	*handle_word(char *str, size_t *index)
{
	char	*str_out;
	size_t	size;

	size = count_word_length(str);
	str_out = ft_substr(str, 0, size);
	*index = *index + size;
	return (str_out);
}
