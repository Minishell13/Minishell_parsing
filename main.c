// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/21 15:58:08 by hwahmane          #+#    #+#             */
// /*   Updated: 2025/02/21 17:35:43 by hwahmane         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <minishell.h>

// void	ft_free(char **get_free)
// {
// 	int	i;

// 	if (!get_free)
// 		return ;
// 	i = 0;
// 	while (get_free[i])
// 	{
// 		free(get_free[i]);
// 		i++;
// 	}
// 	free(get_free);
// 	return ;
// }

// void	ft_write(char **commands, char *path, char *signal, int ft_exit)
// {
// 	if (*commands)
// 		write(2, commands[0], ft_strlen(commands[0]));
// 	if (signal)
// 		write(2, signal, ft_strlen(signal));
// 	write(2, "\n", 1);
// 	if (ft_exit)
// 	{
// 		if (commands)
// 			ft_free(commands);
// 		if (path)
// 			free(path);
// 		exit(127);
// 	}
// }

// char	*get_path(char **paths, char *command)
// {
// 	int		i;
// 	char	*path;
// 	char	*part_path;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, command);
// 		free(part_path);
// 		if (path && access(path, F_OK | X_OK) == 0)
// 			return (path);
// 		free(path);
// 		path = NULL;
// 		i++;
// 	}
// 	free(path);
// 	return (NULL);
// }

// char	*take_path(char **commands, char *command, char **env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path;

// 	i = -1;
// 	while (env[++i] && ft_strnstr(env[i], "PATH", 4) == 0)
// 		;
// 	if (!env[i])
// 		ft_write(commands, NULL, ": not found", 1);
// 	paths = ft_split(env[i] + 5, ':');
// 	if (!paths)
// 		return (NULL);
// 	path = get_path(paths, command);
// 	if (!path)
// 	{
// 		ft_free(paths);
// 		return (NULL);
// 	}
// 	ft_free(paths);
// 	return (path);
// }

// void	check(char *cmd, int *fd)
// {
// 	if (cmd[0] == ' ' || (cmd[0] >= 9 && cmd[0] <= 13))
// 	{
// 		write(2, cmd, ft_strlen(cmd));
// 		write(2, ": not found", 11);
// 		write(2, "\n", 1);
// 		if (fd)
// 		{
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 		exit(1);
// 	}
// 	else if (cmd[0] == '\0')
// 	{
// 		write(2, cmd, ft_strlen(cmd));
// 		write(2, ": Permission denied", 19);
// 		write(2, "\n", 1);
// 		if (fd)
// 		{
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 		exit(1);
// 	}
// }

// void	check_arg(char **commands, char **env)
// {
// 	if (ft_strchr(commands[0], '/'))
// 	{
// 		if (execve(commands[0], commands, env) == -1)
// 		{
// 			write(2, strerror(errno), ft_strlen(strerror(errno)));
// 			write(2, ": ", 2);
// 			ft_write(commands, NULL, NULL, 1);
// 		}
// 	}
// }

// void	exec(char *cmd, char **env)
// {
//     char	**commands;
//     char	*path;
//     pid_t	pid;
//     int		status;

//     check(cmd, NULL);
//     commands = ft_split(cmd, ' ');
//     if (!commands)
//         ft_write(NULL, NULL, "Memory allocation failed", 1);
//     check_arg(commands, env);
//     path = take_path(commands, commands[0], env);
//     if (!path)
//         ft_write(commands, NULL, ": not found", 1);
//     pid = fork();
//     if (pid == 0)
//     {
//         execve(path, commands, env);
//         ft_write(commands, path, ": not found", 1);
//     }
//     else if (pid > 0)
//         waitpid(pid, &status, 0);
//     else
//         perror("fork failed");

//     ft_free(commands);
// }

// char *remove_n(char *command)
// {
//     int i;
//     char *new_command;

//     new_command = malloc(ft_strlen(command));
//     i = 0;
//     while (command[i] != '\n')
//     {
//         new_command[i] = command[i];
//         i++;
//     }
//     new_command[i] = '\0';
//     return (new_command);
// }

// int main(int ac, char **av, char **env)
// {
//     char *command;
//     char *new_command;

//     (void)av;
//     (void)ac;
//     write(1, ">", 1);
//     command = get_next_line(0);
//     while (command)
//     {
//         new_command = remove_n(command);
//         exec(new_command, env);
//         write(1, ">", 1);
//         free(command);
//         free(new_command);
//         command = get_next_line(0);
//     }
//     free(command);
// }
