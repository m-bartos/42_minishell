/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:24:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/02 14:42:21 by mbartos          ###   ########.fr       */
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
- kdyz najdu space/tab, preskakuju a prictu index
- kdyz najdu " -> beru hned jako novy string prvni co je za " a beru vse dokud nenajdu dalsi " (uz jsem predtim ceknul, ze je tam spravny pocet "" a '')
- stejne pokud najdu '

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
			out_str = handle_redirections(&line[i], &i, line[i]);
		else if (line[i] == '|')
			out_str = handle_pipe(&line[i], &i);
		else if (line[i] == '\'' || line[i] == '\"')
			out_str = handle_quotes(&line[i], &i, line[i]);
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

char	**init_arr_of_strs(char *line)
{
	int		count;
	char	**array_of_words;

	count = count_tokens(line);
	array_of_words = (char **) malloc (sizeof(char *) * (count + 1));
	if (!array_of_words)
		return (NULL);
	array_of_words[count] = NULL;
	return (array_of_words);
}

char	**splitter(char *line)
{
	char	**array_of_words;
	size_t	i;
	size_t	j;

	array_of_words = init_arr_of_strs(line);
	if (!array_of_words)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			array_of_words[j++] = handle_redirections(&line[i], &i, line[i]);
		else if (line[i] == '|')
			array_of_words[j++] = handle_pipe(&line[i], &i);
		else if (line[i] == '\'' || line[i] == '\"')
			array_of_words[j++] = handle_quotes(&line[i], &i, line[i]);
		else if (is_whitespace(line[i]))
			i++;
		else
			array_of_words[j++] = handle_word(&line[i], &i);
	}
	return (array_of_words);
}

// cc splitter.c splitter_utils.c ../libft/ft_putnbr_fd.c ../libft/ft_putchar_fd.c -Wall -Wextra -Werror -L/opt/homebrew/opt/readline/lib -lreadline
int	main(void)
{
	char	*line;
	char	**array_of_words;
	// char line[] = "a | b";

	line = readline("Write command: ");
	printf("What I got:    %s\n", line);
	array_of_words = splitter(line);
	// testing:
	int	j;
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
	j = 0;
	while (array_of_words[j] != NULL)
	{
		free(array_of_words[j]);
		j++;
	}
	free(array_of_words[j]);
	free(array_of_words);
	free(line);
	// char	*args[] = {"/bin/echo", "\\n", NULL};
	// execve(args[0], args, NULL);
	return (0);
}
