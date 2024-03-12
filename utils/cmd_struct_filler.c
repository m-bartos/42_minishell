/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:04:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 12:39:52 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// this function will not be needed
void	print_cmd(t_cmd *cmd)
{
	t_token	*token;
	char	**execve_cmd_arr;
	int		i;

	printf("-------------\n");
	i = 0;
	if (cmd->execve_cmd != NULL)
	{
		printf("Execve cmds: {");
		execve_cmd_arr = cmd->execve_cmd;
		while (execve_cmd_arr[i] != NULL)
		{
			printf("%s", execve_cmd_arr[i]);
			if (execve_cmd_arr[i + 1] != NULL)
				printf(", ");
			execve_cmd_arr++;
		}
		printf("}\n");
		printf("-------------\n");
	}
	token = cmd->first_token;
	i = 0;
	while (token != NULL)
	{
		printf("%*i. Token: |%*s|     ", 2, i, 20, token->text);
		printf("Type: %i\n", token->type);
		token = token->next;
		i++;
	}
	printf("-------------\n");
}

void	fill_cmd_tab(t_cmd *cmd, char **arr_of_tokens)
{
	size_t	i;

	i = 0;
	while (arr_of_tokens[i] != NULL)
	{
		ft_push_rotate_token(cmd, arr_of_tokens[i], -1);
		i++;
	}
}
