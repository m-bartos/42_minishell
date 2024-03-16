/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:42:36 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/16 14:50:05 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// init

// add

// remove

// read all

// convert list to array of str

// convert array to list


void	ft_init_env_tab(t_env_tab *tab)
{
	tab->top = NULL;
	tab->size = 0;
}

void	ft_init_env(t_env *env)
{
	env->next = NULL;
	env->value = NULL;
}

void	ft_add_env(t_env_tab *tab, char *env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("Add env:");
		exit(1);
	}
	ft_init_env(node);
	node->value = ft_strdup(env);
	node->next = tab->top;
	tab->top = node;
	tab->size++;
}

// Remove only value from node and set the val to NULL
int	ft_remove_env(t_env_tab *tab, char *env)
{
	t_env	*node;

	node = tab->top;
	while (node)
	{
		if (node->value != NULL)
		{
			if (ft_strncmp(node->value, env, ft_strlen(env) + 1) == 0)
			{
				free(node->value);
				node->value = NULL;
				tab->size--;
				return (0);
			}
		}
		node = node->next;
	}
	return (1);
}

void	ft_list_env(t_env_tab *tab)
{
	t_env	*env;
	env = tab->top;
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->value, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		env = env->next;
	}
}

// Adds strings from envp array passed by main function
void	ft_convert_arr_to_list(t_env_tab *tab, char **envp)
{
	while (*envp)
		ft_add_env(tab, *envp++);
		envp++;
}

char **ft_convert_list_to_arr(t_env_tab *tab)
{
	int		i;
	char	**envp;
	t_env	*env;

	i = 0;
	envp = malloc(sizeof(char *)* (tab->size + 1));
	if (!envp)
	{
		perror("Convert list to arr: ");
		exit(1);
	}
	env = tab->top;
	while (env)
	{
		if (env->value != NULL)
			envp[i] = env->value;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
