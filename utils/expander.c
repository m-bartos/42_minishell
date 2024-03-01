/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:33:30 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/01 13:27:11 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"


char	*get_variable_name(char	*str)
{
	size_t	size_to_malloc;
	size_t	index;
	char	*str_out;

	size_to_malloc = 0;
	while (str[size_to_malloc] != '\0' && str[size_to_malloc] != '/')
		size_to_malloc++;
	str_out = (char *) malloc(sizeof(char) * (size_to_malloc + 1));
	if (!str_out)
		return (NULL);
	index = 0;
	while (index < size_to_malloc)
	{
		str_out[index] = str[index];
		index++;
	}
	str_out[index] = '\0';
	return (str_out);
}

char	*end_of_variable(char *str)
{
	while (*str != '\0' && *str != '/')
		str++;
	return (str);
}

char	*expander(char *str)
{
	size_t	index;
	size_t	j;
	size_t	size_to_malloc;
	char	*str_out;
	char	*str_variable;
	char	*str_expanded_variable;
	char	*str_rest;
	char	*str_old;

	// search str until '$' character is found
	// get the variable name
	// find it in getenv
	// compute the size to allocate new string
	// malloc
	// 

	while (ft_strchr(str, '$'))
	{
		str_variable = ft_strchr(str, '$');
		str_variable = get_variable_name(++str_variable);
		str_expanded_variable = getenv(str_variable);
		free(str_variable);
		size_to_malloc = ft_strchr(str, '$') - str;
		if (str_expanded_variable != NULL)
			size_to_malloc = size_to_malloc + ft_strlen(str_expanded_variable);
		size_to_malloc = size_to_malloc + ft_strchr(str, '\0') - end_of_variable(ft_strchr(str, '$'));
		str_out = (char *) malloc(sizeof(char) * (size_to_malloc + 1));
		if (!str_out)
			return (NULL);
		index = 0;
		while (str[index] != '$')
		{
			str_out[index] = str[index];
			index++;
		}
		j = 0;
		if (str_expanded_variable != NULL)
		{
			while (str_expanded_variable[j] != '\0')
				str_out[index++] = str_expanded_variable[j++];
		}
		str_rest = end_of_variable(ft_strchr(str, '$'));
		j = 0;
		while (str_rest[j] != '\0')
			str_out[index++] = str_rest[j++];
		str_out[index] = '\0';
		str_old = str;
		str = str_out;
		free(str_old);
	}
	return (str);
}

// cc expander.c ../libft/ft_strchr.c ../libft/ft_strlen.c ../libft/ft_strdup.c 

/*
int	main (void)
{
	char	str[] = "aha$PATH/a\n123/$PAT123H/B";
	char	*str_dynamic;

	str_dynamic = ft_strdup(str);	
	printf("INPUT:\n%s\n\n", str_dynamic);
	str_dynamic = expander(str_dynamic);
	printf("OUTPUT:\n%s\n", str_dynamic);
	free(str_dynamic);
}
*/