/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:24:15 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/10 10:24:55 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_program(t_cmd *cmd, char *line, char *prompt)
{
	ft_delete_nodes(cmd);
	free(line);
	free(prompt);
	printf(RESET);
}

void	check_exit(t_cmd *cmd, char *line, char *prompt)
{
	if (ft_strncmp(line, "exit", 5) == 0)
	{
		printf("exit\n");
		free_program(cmd, line, prompt);
		exit(0);
	}
}

void	free_array(char **arr_of_str)
{
	int	index;

	index = 0;
	while (arr_of_str[index] != NULL)
	{
		free(arr_of_str[index]);
		index++;
	}
	free(arr_of_str);
}
