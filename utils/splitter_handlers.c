/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:47:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/02 14:47:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*handle_quotes(char *str, size_t *index, char quotes_type)
{
	size_t	size_to_malloc;
	size_t	j;
	char	*str_out;

	size_to_malloc = 1;
	while (str[size_to_malloc] != quotes_type && str[size_to_malloc] != '\0')
		size_to_malloc++;
	str_out = (char *) malloc(sizeof(char) * (size_to_malloc + 2));
	if (!str_out)
		return (NULL);
	j = 0;
	while (j < size_to_malloc + 1)
	{
		str_out[j] = str[j];
		j++;
	}
	str_out[j] = '\0';
	*index = *index + size_to_malloc + 1;
	return (str_out);
}

char	*handle_word(char *str, size_t *index)
{
	size_t	size_to_malloc;
	size_t	j;
	char	*str_out;

	size_to_malloc = word_length(str);
	str_out = (char *) malloc (sizeof(char) * (size_to_malloc + 1));
	if (!str_out)
		return (NULL);
	*index = *index + size_to_malloc;
	j = 0;
	while (j < size_to_malloc)
	{
		str_out[j] = str[j];
		j++;
	}
	str_out[j] = '\0';
	return (str_out);
}
