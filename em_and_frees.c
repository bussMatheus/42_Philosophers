#include "./philo.h"

//File to secure error managment, sendind necessary messages
// and freeing when necessary

void	error_msg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}

void	destroy_data(t_data *data)
{
	int	i;

	if (!data || !data->forks)
		return ;
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	data->forks = NULL;
}
