/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:24:52 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/02 14:54:12 by mbartos          ###   ########.fr       */
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
- kdyz najdu "<" - kouknu se co je dal, jestli je tam dalsi "<", tak beru "<<",
 pokud neni, beru jen "<"
- stejne pro ">" a ">>"
- kdyz najdu |, beru | jen jednou
- kdyz najdu space/tab, preskakuju a prictu index
- kdyz najdu " -> beru hned jako novy string prvni co je za " a beru vse dokud
 nenajdu dalsi " (uz jsem predtim ceknul, ze je tam spravny pocet "" a '')
- stejne pokud najdu '

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
