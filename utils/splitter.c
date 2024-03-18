/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:24:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 10:55:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Counts the number of tokens in a given line.
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
 * Initializes an array of tokens for line to be split 
 *  - counts tokens in string and allocates memory.
 *
 * @param line The line to be split into an array of tokens.
 * @return An array of strings containing the split tokens from the line.
 */
char	**init_arr_of_tokens(char *line)
{
	int		count;
	char	**array_of_tokens;

	count = count_tokens(line);
	array_of_tokens = (char **) malloc (sizeof(char *) * (count + 1));
	if(array_of_tokens == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	array_of_tokens[count] = NULL;
	return (array_of_tokens);
}

/**
 * Splits a given string into an array of tokens based on certain delimiters.
 *
 * @param line The input string to be split.
 * @return An array of strings, where each element represents a token
 *         from the input string. Returns NULL if memory allocation fails.
 */
char	**splitter(char *line)
{
	char	**array_of_tokens;
	size_t	i;
	size_t	j;

	array_of_tokens = init_arr_of_tokens(line);
	if(array_of_tokens == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			array_of_tokens[j++] = handle_redirections(&line[i], &i);
		else if (line[i] == '|')
			array_of_tokens[j++] = handle_pipe(&line[i], &i);
		else if (is_whitespace(line[i]))
			i++;
		else
			array_of_tokens[j++] = handle_word(&line[i], &i);
	}
	return (array_of_tokens);
}
