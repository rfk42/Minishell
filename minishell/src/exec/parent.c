/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:57:29 by rhamini           #+#    #+#             */
/*   Updated: 2024/10/04 14:57:31 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect(t_cmd *cmd)
{
	if (cmd->infile > STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile > STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
}

static void	exec_builtins(t_token *list, t_cmd *cmd, t_mem *mem)
{
	builtins(list, mem);
	if (cmd->infile > STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile > STDOUT_FILENO)
		close(cmd->outfile);
	free(cmd->command);
	free_tab(cmd->args);
	close(mem->saved_stdin);
	close(mem->saved_stdout);
	exit(0);
}

static void	clear_execve(t_cmd *cmd, t_mem *mem)
{
	perror("execve");
	if (cmd->infile > STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile > STDOUT_FILENO)
		close(cmd->outfile);
	free(cmd->command);
	free_tab(cmd->args);
	close(mem->saved_stdin);
	close(mem->saved_stdout);
	exit(0);
}

static void	deal_pipe(t_cmd *cmd)
{
	close(cmd->fd[0]);
	if (cmd->outfile <= STDOUT_FILENO)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
	else
		close(cmd->fd[1]);
}

void	do_command(t_token *list, t_cmd *cmd, t_mem *mem, int status)
{
	mem->pids[mem->index] = fork();
	if (mem->pids[mem->index] < 0)
		perror("Fork error");
	if (mem->pids[mem->index] == 0)
	{
		redirect(cmd);
		child_sig_init();
		if (status == 1)
			deal_pipe(cmd);
		if (is_builtins(cmd->command))
			exec_builtins(list, cmd, mem);
		else
		{
			if (execve(cmd->command, cmd->args, mem->envp) == -1)
				clear_execve(cmd, mem);
		}
	}
}
