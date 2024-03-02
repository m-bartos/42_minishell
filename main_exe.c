/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:36:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 13:36:01 by aldokezer        ###   ########.fr       */
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
	ft_print_cmd(&cmd_table);
	return (0);
}
