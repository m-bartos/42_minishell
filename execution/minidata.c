/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minidata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:20 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/20 10:43:03 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_mini_data(t_mini_data *minidata, t_cmd_tab *cmd_tab,
	char *envp[])
{
	t_env_list	*env_list;

	env_list = malloc(sizeof(t_env_list));
	minidata->cmd_tab = cmd_tab;
	minidata->env_list = env_list;
	ft_init_env_list(minidata->env_list);
	ft_convert_arr_to_list(minidata->env_list, envp);
	ft_add_env(minidata->env_list, "?=0");
	minidata->env_arr = ft_convert_list_to_arr(minidata->env_list);
}
