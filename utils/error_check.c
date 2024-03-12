/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:29:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 12:52:11 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_unclosed_quotes(char *str)
{
	int		search_single_q;
	int		search_double_q;

	search_single_q = 1;
	search_double_q = 1;
	if (str == NULL)
		return (-1);
	while (*str)
	{
		if (*str == '\"' && search_double_q == 1 && search_single_q == 1)
			search_single_q = 0;
		else if (*str == '\'' && search_double_q == 1 && search_single_q == 1)
			search_double_q = 0;
		else if (*str == '\"' && search_double_q == 1 && search_single_q == 0)
			search_single_q = 1;
		else if (*str == '\'' && search_double_q == 0 && search_single_q == 1)
			search_double_q = 1;
		str++;
	}
	if (search_single_q == search_double_q)
		return (0);
	else
		return (1);
}

void	check_unclosed_quotes(char *line)
{
	if (is_unclosed_quotes(line) == 1)
	{
		printf("Minishell cannot handle open quotes (\", \').\n");
		free(line);
		printf(RESET);
		exit(0);
	}
}
