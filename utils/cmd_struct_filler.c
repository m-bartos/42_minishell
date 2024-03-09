/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:04:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/09 18:22:28 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// this function will not be needed
void	print_cmd(t_cmd *ptr_cmd)
{
	t_token	*ptr_token;
	char	**execve_cmd_arr;
	int		i;

	printf("-------------\n");
	i = 0;
	if (ptr_cmd->execve_cmd != NULL)
	{
		printf("Execve cmds: {");
		execve_cmd_arr = ptr_cmd->execve_cmd;
		while(execve_cmd_arr[i] != NULL)
		{
			printf("%s",execve_cmd_arr[i]);
			if (execve_cmd_arr[i + 1] != NULL)
				printf(", ");
			execve_cmd_arr++;
		}
		printf("}\n");
		printf("-------------\n");
	}
	ptr_token = ptr_cmd->first_token;
	i = 0;
	while (ptr_token != NULL)
	{
		printf("%*i. Token: |%*s|     ", 2, i, 20, ptr_token->text);
		printf("Type: %i\n", ptr_token->type);
		ptr_token = ptr_token->next;
		i++;
	}
	printf("-------------\n");
}

void	fill_cmd_tab(t_cmd *ptr_cmd, char **arr_of_tokens)
{
	size_t	index;

	index = 0;
	while (arr_of_tokens[index])
	{
		ft_push_rotate_token(ptr_cmd, arr_of_tokens[index], -1);
		index++;
	}
}
