/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:36:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/08 16:49:33 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{

	char *cmd1[] = {"/bin/ls", "-la", NULL};
	char *cmd2[] = {"/usr/bin/wc", "-l", NULL};

	char **cmds[] = {cmd1, cmd2, NULL};

	ft_exec_commands(cmds);

	return (0);
}
