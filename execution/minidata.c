/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minidata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:20 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/18 18:08:32 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_mini_data(t_mini_data *minidata, char *envp[])
{
	// Free space after use!
	// malloc env_list, and its variables
	// env_var values point to env_list values thus no need to free them
	// env_var is supposed to be freed
	t_env_list	*env_list;
	env_list = malloc(sizeof(t_env_list));

	minidata->env_list = env_list;
	ft_init_env_list(minidata->env_list);
	ft_convert_arr_to_list(minidata->env_list, envp);
	ft_add_env(minidata->env_list, "?=-99");
	minidata->env_arr = ft_convert_list_to_arr(minidata->env_list);
}
