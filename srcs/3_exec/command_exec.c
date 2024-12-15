#include "minishell.h"

char	**env_extract_paths(char **env)
{
	t_env	*tmp;
	char	*path;
	char	**path_file;

	tmp = env;
	path = NULL;
	while (tmp)
	{
		if (ft_strnstr(tmp->type, "PATH", 4))
		{
			path = ft_strdup(tmp->value + 5);
			if (!path)
				return (NULL);
			break ;
		}
		tmp = tmp->next;
	}
	if (ft_strlen(path) == 0 || path == NULL)
		path_file = ft_split(".", ':');
	else
	{
		path_file = ft_split(path, ':');
		free(path);
	}
	return (path_file);
}

char	*search_cmd_path(t_data *data, t_commands *cmd, char **env)
{
	char	**path;
	char	*cmd_path;
	char	*sub;
	int		i;

	i = 0;
	if (!data->cpy_env)
		return (data->err = 1, NULL);
	path = recup_path(data->cpy_env);
	if (!*path || !path)
		return (NULL);
	sub = ft_strjoin("/", cmd);
	if (!cmd || !sub)
		return (ft_free_tab(path), NULL);
	while (path[i] && path)
	{
		cmd_path = ft_strjoin(path[i], sub);
		if (!cmd_path)
			return (ft_free_tab(path), free(sub), data->err = 1, NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_free_tab(path), free(sub), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_tab(path), free(sub), ft_strdup(""));
}

static char	*valid_path(t_data *data, t_commands *cmd)
{
    char	*exec_path;
	char	**new_env;

	exec_path = 0;
	update_last_cmd(data, exec_path);
	new_env = env_to_tab(data->cpy_env);
    if (!new_env)
		return (data->err = 1, failed_mess(data, "malloc failed", 1), 0);
	if (access(cmd->command, X_OK | F_OK) == 0)
        return (ft_free_tab(new_env), cmd->command);
	else
		exec_path = search_cmd_path(data, cmd, new_env);
	if (exec_path)
		return (ft_free_tab(new_env),exec_path);
	else
	{
		data->exit_status = 127;
		free(exec_path);
        ft_free_tab(new_env);
	}
    return (NULL);
}

int	command_executer(t_commands *command, t_data *data)
{
	char	*exec_path;
	char	**new_env;

	if (!command || !command->command)
		return (EXIT_FAILURE);
	exec_path = valid_path(data, command);
    if (!exec_path)
    {
        ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->command, 2);
		ft_putstr_fd(": command not found\n", 2);
		//  = NOT_FOUND;
    }
	update_last_cmd(data, exec_path);
	new_env = env_to_tab(data->cpy_env);
	if (!new_env)
		return (data->err = 1, failed_mess(data, "malloc failed", 1), 0);
	data->exit_status = execve(exec_path, command->final_group, new_env);
	free(exec_path);
    ft_free_tab(new_env);
	exit(data->exit_status);
}
