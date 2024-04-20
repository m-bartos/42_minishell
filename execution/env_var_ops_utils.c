/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_ops_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:29:47 by aldokezer         #+#    #+#             */
/*   Updated: 2024/04/20 10:30:49 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Converts an array of strings to a list of variables.
 *
 * Each string representing an environment variable is added to the list.
 *
 * @param env_list Pointer to the environment list.
 * @param envp Array of strings of environment variables.
 */

void	ft_convert_arr_to_list(t_env_list *env_list, char **envp)
{
	while (*envp)
	{
		ft_add_env(env_list, *envp);
		envp++;
	}
}

/**
 * @brief Converts a list of variables to an array of strings.
 *
 * Creates an array of strings from the list, ending with NULL.
 *
 * @param env_list Pointer to the environment list.
 * @return Array of strings representing the environment variables.
 */

char	**ft_convert_list_to_arr(t_env_list *env_list)
{
	int		i;
	char	**envp;
	t_env	*env;

	i = 0;
	envp = malloc(sizeof(char *) * (env_list->size + 1));
	if (!envp)
	{
		perror("Convert list to arr: ");
		exit(1);
	}
	env = env_list->top;
	while (env)
	{
		if (env->env_text != NULL)
		{
			envp[i] = env->env_text;
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
