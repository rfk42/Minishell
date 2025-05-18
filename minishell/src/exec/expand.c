/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:23:05 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/10 13:21:27 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_name_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static void	ft_replace(t_expand *t, char *str, t_env *env, t_mem *mem)
{
	t->n = 0;
	(t->i)++;
	if (!str[t->i])
		t->sub = ft_strdup("$");
	else if (str[t->i] == '?' && !str[t->i + 1])
	{
		(t->n)++;
		t->sub = ft_itoa(mem->exit_stat);
	}
	else
	{
		while (is_name_char((int)str[t->i + t->n]))
			(t->n)++;
		t->key = ft_substr(str, t->i, t->n);
		if (my_getenv(t->key, env))
			t->sub = ft_strdup(my_getenv(t->key, env));
		else
			t->sub = ft_strdup("");
		if (t->key)
			free(t->key);
	}
}

static char	*expansion(char *str, t_env *env, t_mem *mem)
{
	t_expand	t;

	t.i = 0;
	t.s = ft_strdup("");
	t.sub = NULL;
	t.key = NULL;
	t.len = ft_strlen(str);
	while (t.i < t.len)
	{
		if (str[t.i] == '$')
			ft_replace(&t, str, env, mem);
		else
		{
			t.n = ft_strchr(str + t.i, '$');
			t.sub = ft_substr(str + t.i, 0, t.n);
		}
		t.s = spe_strjoin(t.s, t.sub);
		if (t.sub)
			free(t.sub);
		t.sub = NULL;
		t.i += t.n;
	}
	free(str);
	return (t.s);
}

int	handle_expansion(t_token *temp, t_env *env, t_mem *mem)
{
	char	*s;

	if (temp->type == SINGLEQUOTE || temp->type == DOUBLEQUOTE)
		s = ft_substr(temp->value, 1, ft_strlen(temp->value) - 2);
	else
		s = ft_strdup(temp->value);
	if (!s)
		return (0);
	if ((temp->type == DOUBLEQUOTE || temp->type == ARGUMENT
			|| temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT)
		&& ft_strlen(temp->value) > 1)
		s = expansion(s, env, mem);
	if (!s)
		return (0);
	free(temp->value);
	temp->value = s;
	if (temp->type == ARGUMENT && ft_strchr(temp->value, '*')
		< ft_strlen(temp->value))
		expand_from_wc(&temp);
	return (1);
}

int	command_check(t_token *list, t_mem *mem)
{
	t_token	*temp;
	int		n;

	temp = list;
	n = 0;
	while (temp)
	{
		if (is_end_command(temp) && n)
			n = 0;
		else if (is_end_command(temp) && !n)
		{
			mem->exit_stat = 2;
			return (printf("Error: command missing\n"), 0);
		}
		if (temp->type == COMMAND)
			n = 1;
		temp = temp->next;
	}
	if (!n)
	{
		mem->exit_stat = 2;
		return (printf("Error: command missing\n"), 0);
	}
	return (1);
}
