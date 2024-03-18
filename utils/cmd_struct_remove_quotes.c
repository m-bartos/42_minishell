/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 10:48:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	count_substrs_in_word(char const *text)
{
	char	*temp_str;
	size_t	i;
	int		size;

	i = 0;
	size = 0;
	while (text[i])
	{
		temp_str = get_substr_from_word(&text[i], &i);
		free(temp_str);
		size++;
	}
	return (size);
}

char	**parse_token_text(char *text)
{
	char	**arr_of_strs;
	size_t	i;
	size_t	j;
	int		size;

	size = count_substrs_in_word(text);
	arr_of_strs = ft_init_array(size);
	i = 0;
	j = 0;
	while (text[i])
		arr_of_strs[j++] = get_substr_from_word(&text[i], &i);
	return (arr_of_strs);
}

void	remove_quotes_in_token(t_token *token)
{
	char	*new_token;
	char	*temp_token_text;
	char	**arr_of_strs;

	arr_of_strs = parse_token_text(token->text);
	arr_of_strs = remove_quotes_encaptulates_words(arr_of_strs);
	new_token = ft_arr_to_str(arr_of_strs);
	ft_free_array(arr_of_strs);
	temp_token_text = token->text;
	token->text = new_token;
	free(temp_token_text);
}

void	remove_quotes_in_cmd_tokens(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token != NULL)
	{
		if (!is_operator_type(token))
			remove_quotes_in_token(token);
		token = token->next;
	}
}
