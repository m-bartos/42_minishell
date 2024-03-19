/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:24:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/19 11:03:35 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Counts the number of tokens in a given line.
 *
 * @param line The input line to be split into tokens.
 * @return The number of tokens found in the line.
 */
int	count_tokens(char *line)
{
	size_t	count;
	size_t	i;
	char	*out_str;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			out_str = handle_redirections(&line[i], &i);
		else if (line[i] == '|')
			out_str = handle_pipe(&line[i], &i);
		else if (is_whitespace(line[i]))
		{
			i++;
			continue ;
		}
		else
			out_str = handle_word(&line[i], &i);
		free(out_str);
		count++;
	}
	return (count);
}

/**
 * @brief Initializes an array of tokens for line to be split 
 *  - counts tokens in string and allocates memory.
 *
 * @param line The line to be split into an array of tokens.
 * @return An array of strings containing the split tokens from the line.
 */
char	**init_tokens_arr(char *line)
{
	int		count;
	char	**tokens_arr;

	count = count_tokens(line);
	tokens_arr = (char **) malloc (sizeof(char *) * (count + 1));
	if(tokens_arr == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	tokens_arr[count] = NULL;
	return (tokens_arr);
}

/**
 * @brief Splits a given string into an array of tokens based on delimiters.
 *
 * @param line The input string to be split.
 * @return An array of strings, where each element represents a token
 *         from the input string. Returns NULL if memory allocation fails.
 */
char	**splitter(char *line)
{
	char	**tokens_arr;
	size_t	i;
	size_t	j;

	tokens_arr = init_tokens_arr(line);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			tokens_arr[j++] = handle_redirections(&line[i], &i);
		else if (line[i] == '|')
			tokens_arr[j++] = handle_pipe(&line[i], &i);
		else if (is_whitespace(line[i]))
			i++;
		else
			tokens_arr[j++] = handle_word(&line[i], &i);
	}
	return (tokens_arr);
}
