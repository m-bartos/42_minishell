/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_remove_quotes_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:52:08 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 17:06:22 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd_struct_remove_quotes_utils.c
 * @brief Utility functions for removing quotes from token text within command
 * structures.
 *
 * This file contains utility functions used in the process of removing quotes
 * from token text within command structures. It includes functions for parsing
 * token text, removing quotes encaptulating words, and obtaining substrings
 * from words.
 */

#include "../minishell.h"

/**
 * @brief Removes quotes encaptulating words from an array of strings.
 * 
 * This function removes quotes ('"' or '\'') encaptulating words within each
 * string of the specified array. It iterates through the array and trims quotes
 * from the beginning and end of each string if present.
 * 
 * @param arr_of_str The array of strings to process.
 * @return The updated array of strings with quotes removed from each word.
 */
char	**remove_quotes_encaptulates_words(char **arr_of_str)
{
	size_t	i;
	char	*temp_str;

	i = 0;
	while (arr_of_str[i])
	{
		if (arr_of_str[i][0] == '\"')
		{
			temp_str = arr_of_str[i];
			arr_of_str[i] = ft_strtrim_e(arr_of_str[i], "\"");
			free(temp_str);
		}
		else if (arr_of_str[i][0] == '\'')
		{
			temp_str = arr_of_str[i];
			arr_of_str[i] = ft_strtrim_e(arr_of_str[i], "\'");
			free(temp_str);
		}
		i++;
	}
	return (arr_of_str);
}

/**
 * @brief Obtains a substring from a word in the given text.
 * 
 * This function extracts a substring from a word in the specified text.
 * It identifies the end of the word based on the specified letter to find 
 * (quote character). It then calculates the size of the substring and obtains
 * it.
 * 
 * @param str The text containing the word.
 * @param i Pointer to the index indicating the position within the text.
 * @return The substring extracted from the word.
 */
char	*get_substr_from_word(char const *str, size_t *i)
{
	char	letter_to_find;
	char	*end_of_word;
	size_t	size;
	char	*new_text;

	letter_to_find = str[0];
	size = 0;
	if (letter_to_find != '\'' && letter_to_find != '\"')
	{
		if (ft_strchrnul(str, '\'') > ft_strchrnul(str, '\"'))
			end_of_word = ft_strchrnul(str, '\"');
		else
			end_of_word = ft_strchrnul(str, '\'');
		size = end_of_word - str;
	}
	else
		size = ft_strchr(&str[1], letter_to_find) - str + 1;
	new_text = ft_substr_e(str, 0, size);
	*i = *i + size;
	return (new_text);
}

/**
 * @brief Counts the number of substrings in a word within the text.
 * 
 * @param text The text to process.
 * @return The number of substrings in the word.
 */
int	count_substrs_in_word(char const *word)
{
	char	*temp_str;
	size_t	i;
	int		size;

	i = 0;
	size = 0;
	while (word[i])
	{
		temp_str = get_substr_from_word(&word[i], &i);
		free(temp_str);
		size++;
	}
	return (size);
}

/**
 * @brief Parses token text into an array of strings.
 * 
 * This function parses the specified token text into an array of strings.
 * It counts the number of substrings in the text, allocates memory for
 * the array, and obtains substrings from token text.
 * 
 * @param text The token text to parse.
 * @return The array of strings containing parsed words from the token text.
 */
char	**parse_token_text(char *word)
{
	char	**arr_of_strs;
	size_t	i;
	size_t	j;
	int		size;

	size = count_substrs_in_word(word);
	arr_of_strs = ft_init_array(size);
	i = 0;
	j = 0;
	while (word[i])
		arr_of_strs[j++] = get_substr_from_word(&word[i], &i);
	return (arr_of_strs);
}
