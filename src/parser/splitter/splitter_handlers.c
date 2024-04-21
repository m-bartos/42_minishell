/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:47:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/21 20:23:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extracts redirections (<, <<, >, >>) from a string.
 * 
 * This function takes a string, an index as input.
 * It creates a new string containing the redirection symbol(s) 
 * at the beginning of the original string.
 * The size of the new string is determined based on the redirection type.
 * The index is updated to reflect the number of characters processed.
 * 
 * @param str The original string.
 * @param index A pointer to the current index in the string.
 * @return A new string containing the redirection symbol(s).
 */
char	*handle_redirections(char *str, size_t *index)
{
	size_t	size;
	char	*str_out;

	if (str[1] == str[0])
		size = 2;
	else
		size = 1;
	str_out = ft_substr_e(str, 0, size);
	*index = *index + size;
	return (str_out);
}

/**
 * @brief Extracts the pipe character from a string.
 *
 * This function takes a string and an index as input and returns a new string
 * containing the pipe character at the start of string. The index is updated 
 * by one to reflect the number of characters processed.
 *
 * @param str The input string.
 * @param index A pointer to the current index in the string.
 * @return A new string containing the pipe character.
 */
char	*handle_pipe(char *str, size_t *index)
{
	char	*str_out;
	size_t	size;

	size = 1;
	str_out = ft_substr_e(str, 0, size);
	*index = *index + size;
	return (str_out);
}

/**
 * @brief Handles a word in a string and returns it.
 * 
 * This function takes a string and an index as input. It counts the length of
 * the word starting from the given index, creates a new string containing
 * the word, and updates the index to the next position after the word.
 * The newly created string is then returned.
 * 
 * @param str The input string.
 * @param index A pointer to the current index in the string.
 * @return The word extracted from the string.
 */
char	*handle_word(char *str, size_t *index)
{
	char	*str_out;
	size_t	size;

	size = count_word_length(str);
	str_out = ft_substr_e(str, 0, size);
	*index = *index + size;
	return (str_out);
}
