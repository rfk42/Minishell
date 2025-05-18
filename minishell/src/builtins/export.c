/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrischma <hrischma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:24:54 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/10 13:38:08 by hrischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_for_export(char *s)
{
	int	i;
	int	j;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 0;
	j = ft_strchr(s, '=');
	while (i < j)
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	update_if_equal(char *s, size_t equal_pos, t_env *temp, t_env *node)
{
	if (equal_pos != ft_strlen(s) && s[equal_pos + 1])
	{
		free(temp->value);
		temp->value = ft_strdup(node->value);
	}
	free(node);
}

t_env	*add_env_for_export(char *s, t_env **env)
{
	t_env	*node;
	t_env	*temp;
	size_t	equal_pos;

	equal_pos = ft_strchr(s, '=');
	node = env_new_node(s);
	if (!node || (!*env || !(*env)->key))
		return (*env = node, node);
	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(node->key, temp->key))
			return (update_if_equal(s, equal_pos, temp, node), NULL);
		if (!temp->next || ft_strcmp(node->key, temp->next->key) < 0)
			break ;
		temp = temp->next;
	}
	node->next = temp->next;
	temp->next = node;
	return (node);
}

static int	ft_print_export(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->is_unset == 0)
		{
			if (ft_strcmp(temp->value, "") > 0)
				printf("export %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("export %s\n", temp->key);
		}
		temp = temp->next;
	}
	return (1);
}

int	ft_export(t_env *env, t_token *arg, t_mem *mem)
{
	t_token	*temp;
	int		i;

	temp = arg->next;
	i = 0;
	if (is_end_command(temp))
		return (ft_print_export(env));
	while (!is_end_command(temp))
	{
		if (is_valid_for_export(temp->value))
		{
			add_env_for_export(temp->value, &env);
			add_env_for_export(temp->value, &(mem->my_env));
		}
		else
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				temp->value);
			i = 1;
		}
		temp = temp->next;
	}
	mem->exit_stat = i;
	return (1);
}
