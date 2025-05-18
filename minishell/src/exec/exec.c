/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:22:53 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 14:48:03 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_pipes(t_token *list)
{
	int		num;
	t_token	*temp;

	num = 0;
	temp = list;
	while (temp)
	{
		if (!ft_strcmp(temp->value, "|"))
			num++;
		temp = temp->next;
	}
	return (num);
}

void	get_exit_stat(char *s, t_mem *mem)
{
	if (is_builtins(s))
		return ;
	if (WIFSIGNALED(mem->status))
		mem->exit_stat = 128 + WTERMSIG(mem->status);
	else if (WIFEXITED(mem->status))
		mem->exit_stat = WEXITSTATUS(mem->status);
	else if (WIFSTOPPED(mem->status))
		mem->exit_stat = 128 + WSTOPSIG(mem->status);
	if (mem->exit_stat == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (mem->exit_stat == 128 + SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
}

static void	end_exec(t_mem *mem, int num)
{
	int		i;

	i = 0;
	dup2(mem->saved_stdin, STDIN_FILENO);
	dup2(mem->saved_stdout, STDOUT_FILENO);
	while (i < num)
	{
		if (mem->pids[i] != -1)
			waitpid(mem->pids[i], &(mem->status), 0);
		i++;
	}
	if (mem->wait)
	{
		if (mem->pids[i] != -1)
			waitpid(mem->pids[i], &(mem->status), 0);
	}
	free(mem->pids);
}

static void	mem_setup(t_mem *mem)
{
	int	i;

	i = 0;
	mem->index = 0;
	while (i <= mem->pipe_num)
	{
		mem->pids[i] = -1;
		i++;
	}
}

int	exec(t_mem *mem)
{
	t_token	*temp;

	temp = mem->tokens;
	if (!command_check(mem->tokens, mem)
		|| !expand(&(mem->tokens), mem->values, mem))
		return (0);
	mem->pipe_num = count_pipes(temp);
	mem->pids = malloc((mem->pipe_num + 1) * sizeof (pid_t *));
	if (!mem->pids)
		return (0);
	mem_setup(mem);
	signal(SIGINT, SIG_IGN);
	while (mem->index < mem->pipe_num)
	{
		ft_command(temp, mem);
		while (!is_end_command(temp))
			temp = temp->next;
		temp = temp->next;
		(mem->index)++;
	}
	last_child(temp, mem);
	end_exec(mem, mem->pipe_num);
	if (mem->cmd_exist)
		get_exit_stat(mem->last_cmd, mem);
	return (1);
}
