/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:36:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 22:30:13 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	t_command_table cmd_table;
	char	**arr;

	ft_init_command_table(&cmd_table);
	char	*command = "ls -la | wc -l";
	arr = ft_split(command, ' ');
	while (*arr)
	{
		ft_push_rotate_token(&cmd_table, *arr);
		arr++;
	}

	char *cmd1[] = {"/bin/ls", "-la", NULL};
	char *cmd2[] = {"/usr/bin/wc", "-l", NULL};
	char *cmd3[] = {"/usr/bin/wc", "-c", NULL};
	char **cmds[] = {cmd1, cmd2, cmd3, NULL};

	ft_exec_commands(cmds);
	return (0);
}
