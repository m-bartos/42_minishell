/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:24:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/02 13:17:13 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// SPLITTER
/*

Parse by space
parse by quotes
Parse by <, >, |, <<, >> (if not in quotes)


< infile.txt cat | cat > outfile.txt


1. hledam <, >, <<, >>, space/tab, quotes
- kdyz najdu "<" - kouknu se co je dal, jestli je tam dalsi "<", tak beru "<<", pokud neni, beru jen "<"
- stejne pro ">" a ">>"
- kdyz najdu |, beru | jen jednou
- kdyz najdu space/tab, kouknu jestli je dalsi taky space/tab, pokud jo, jdu dal dokud nenajdu neco jineho
- kdyz najdu " -> beru hned jako novy string prvni co je za " a beru az nez najdu ending " (uz jsem predtim ceknul, ze je tam spravny pocet "" a '')
- stejne pokud najdu '

*/
char	*handle_redirect_input(char *str, size_t *index)
{
	size_t	size_to_malloc;
	size_t	j;
	char	*str_out;

	if (str[1] == '<')
		size_to_malloc = 2;
	else
		size_to_malloc = 1;
	str_out = (char*) malloc(sizeof(char) * size_to_malloc + 1);
	if (!str_out)
		return (NULL);
	str_out[size_to_malloc] = '\0';
	j = 0;
	while (j < size_to_malloc)
	{
		str_out[j] = str[j];
		j++;
	}
	*index = *index + size_to_malloc;
	return (str_out);
}

char	*handle_redirect_output(char *str, size_t *index)
{
	size_t	size_to_malloc;
	size_t	j;
	char	*str_out;

	if (str[1] == '>')
		size_to_malloc = 2;
	else
		size_to_malloc = 1;
	str_out = (char*) malloc(sizeof(char) * size_to_malloc + 1);
	if (!str_out)
		return (NULL);
	str_out[size_to_malloc] = '\0';
	j = 0;
	while (j < size_to_malloc)
	{
		str_out[j] = str[j];
		j++;
	}
	*index = *index + size_to_malloc;
	return (str_out);
}

char	*handle_pipe(char *str, size_t *index)
{
	char	*str_out;

	str_out = (char*) malloc(sizeof(char) * 2);
	if (!str_out)
		return (NULL);
	str_out[0] = str[0];
	str_out[1] = '\0';
	*index = *index + 1;
	return (str_out);
}

char	*handle_single_quotes(char *str, size_t *index)
{
	size_t	size_to_malloc;
	size_t	j;
	char	*str_out;

	size_to_malloc = 1;
	while (str[size_to_malloc] != '\'' && str[size_to_malloc] != '\0')
		size_to_malloc++;
	str_out = (char *) malloc(sizeof(char) * (size_to_malloc + 1));
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

char	*handle_double_quotes(char *str, size_t *index)
{
	size_t	size_to_malloc;
	size_t	j;
	char	*str_out;

	size_to_malloc = 1;
	while (str[size_to_malloc] != '\"' && str[size_to_malloc] != '\0')
		size_to_malloc++;
	str_out = (char *) malloc(sizeof(char) * (size_to_malloc + 1));
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

char	*handle_word_outside_quotes(char *str, size_t *index)
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

void	splitter(char *line)
{
	char	*array_of_words[30];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			array_of_words[j] = handle_redirect_input(&line[i], &i);
			j++;
		}
		else if (line[i] == '>')
		{
			array_of_words[j] = handle_redirect_output(&line[i], &i);
			j++;
		}
		else if (line[i] == '|')
		{
			array_of_words[j] = handle_pipe(&line[i], &i);
			j++;
		}
		else if (line[i] == '\'')
		{
			array_of_words[j] = handle_single_quotes(&line[i], &i);
			j++;
		}
		else if (line[i] == '\"')
		{
			array_of_words[j] = handle_double_quotes(&line[i], &i);
			j++;
		}
		else if (is_whitespace(line[i]))
			i++;
		else
		{
			array_of_words[j] = handle_word_outside_quotes(&line[i], &i);
			j++;
		}
	}
	array_of_words[j] = NULL;

	// testing:
	printf("-----------------------------------\n");
	printf("----EACH WORD ON SEPERATED LINE----\n");
	printf("-----------------------------------\n");
	j = 0;
	while (array_of_words[j] != NULL)
	{
		printf("%s", array_of_words[j]);
		printf("\n");
		j++;
	}
	printf("-----------------------------------\n");
	printf("-----------------END---------------\n");
	printf("-----------------------------------\n");
}

#include <readline/readline.h>
// cc splitter.c -Wall -Wextra -Werror -L/opt/homebrew/opt/readline/lib -lreadline


int	main(void)
{
	char	*line;
	// char line[] = "a | b";

	line = readline("Write command: ");
	printf("What I got:    %s\n", line);
	splitter(line);

	// char	*args[] = {"/bin/echo", "\\n", NULL};
	// execve(args[0], args, NULL);
	return (0);
}
