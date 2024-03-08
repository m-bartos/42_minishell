/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:36:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/08 10:43:02 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int	main(void)
// {
// 	t_cmd_tab cmd_table;
// 	char	**arr;

// 	ft_init_command_table(&cmd_table);
// 	char	*command = "ls -la | wc -l";
// 	arr = ft_split(command, ' ');
// 	while (*arr)
// 	{
// 		ft_push_rotate_token(&cmd_table, *arr);
// 		arr++;
// 	}

// 	char *cmd8[] = {"<", NULL};
// 	char *cmd9[] = {"infile.txt", NULL};
// 	char *cmd0[] = {"/bin/cat", NULL};
// 	char *cmd1[] = {"/bin/ls", "-la", NULL};
// 	char *cmd2[] = {"/usr/bin/wc", "-l", NULL};
// 	char *cmd3[] = {"/usr/bin/wc", "-c", NULL};
// 	char *cmd4[] = {"/bin/cat", NULL};
// 	char **cmds[] = {cmd8, cmd9, cmd0, cmd1, cmd2, cmd3, cmd4, NULL};
// 	//char **cmds[] = {cmd8, cmd9, cmd0, NULL};

// 	ft_exec_commands(cmds);

// 	return (0);
// }
