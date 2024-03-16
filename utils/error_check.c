/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:29:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/16 20:43:13 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_unclosed_quotes(char *line)
{
	if (in_which_quotes(line, ft_strlen(line)) == IN_SINGLE_QUOTES
		|| in_which_quotes(line, ft_strlen(line)) == IN_DOUBLE_QUOTES)
	{
		ft_putstr_fd("Minishell cannot handle open quotes (\", \').\n", STDERR);
		free(line);
		printf(RESET);
		exit(31);
	}
}
