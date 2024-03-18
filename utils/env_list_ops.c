/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:36:12 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/18 11:58:39 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Initializes an environment list.
 *
 * Sets the top pointer of the environment list to NULL and initializes the
 * size to 0, effectively creating an empty list.
 *
 * @param env_list Pointer to the environment list to be initialized.
 */

void	ft_init_env_list(t_env_list *env_list)
{
	env_list->top = NULL;
	env_list->size = 0;
}

/**
 * @brief Initializes an environment node.
 *
 * Sets the next pointer of the environment node to NULL and initializes the
 * value to NULL, effectively creating an empty node.
 *
 * @param env Pointer to the environment node to be initialized.
 */
void	ft_init_env(t_env *env)
{
	env->next = NULL;
	env->env_text = NULL;
	env->env_name = NULL;
	env->env_value = NULL;
}
