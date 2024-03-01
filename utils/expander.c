/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:33:30 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/01 19:14:08 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

char	*end_of_variable(char *str)
{
	while (*str != '$' && *str != '\0' && *str != '/' && *str != ':' && *str != '^'
		&& *str != ';' && *str != '-' && *str != '%' && *str != '&' && *str != '*' && *str != '#' && *str != '@')
		str++;
	return (str);
}

char	*get_variable_name(char	*str)
{
	size_t	size_to_malloc;
	size_t	index;
	char	*str_variable;
	char	*str_out;	

	str_variable = ft_strchr(str, '$') + 1;
	size_to_malloc = end_of_variable(str_variable) - str_variable;
	str_out = (char *) malloc(sizeof(char) * (size_to_malloc + 1));
	if (!str_out)
		return (NULL);
	index = 0;
	while (index < size_to_malloc)
	{
		str_out[index] = str_variable[index];
		index++;
	}
	str_out[index] = '\0';
	return (str_out);
}

char	*find_and_expand_var(char *str)
{
	char	*str_variable;
	char	*str_extended_variable;

	str_variable = get_variable_name(str);
	str_extended_variable = getenv(str_variable);
	free(str_variable);
	return (str_extended_variable);
}

	// WHILE LOOP (until all variables are expanded in the string)
	// search str until '$' character is found
	// get the variable name (behind $)
	// find it with getenv() function
	// compute the size to allocate new string
	// malloc
	// make a new string with expanded variable
	// WHILE LOOP
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

	while (ft_strchr(str, '$'))
	{
		str_expanded_variable = find_and_expand_var(str);
		size_to_malloc = ft_strchr(str, '$') - str;
		if (str_expanded_variable != NULL)
			size_to_malloc = size_to_malloc + ft_strlen(str_expanded_variable);
		size_to_malloc = size_to_malloc + ft_strchr(str, '\0') - end_of_variable(ft_strchr(str, '$') + 1);
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
		str_rest = end_of_variable(ft_strchr(str, '$') + 1);
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

int	main (void)
{
	char	str[] = "a/$PATH/a";
	char	*str_dynamic;

	str_dynamic = ft_strdup(str);
	printf("INPUT:\n%s\n\n", str_dynamic);
	str_dynamic = expander(str_dynamic);
	printf("OUTPUT:\n%s\n", str_dynamic);
	free(str_dynamic);
}


// ---CHECKERS BEFORE EXECUTION---
// folder permission check
// double PIPE, double < <, double > >
// INFILE checker