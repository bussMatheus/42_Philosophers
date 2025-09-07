#include "./philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_print_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_data(int ac, char **av, t_data *data)
{
	data->n_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->num_meals = ft_atol(av[5]);
	else
		data->num_meals = -1;
	data->someone_died = false;
	data->start_time = get_time();
	if (data->start_time == -1)
		return (error_msg("Error getting the actual time"), 1);
	if (init_print_mutex(data))
		return (error_msg("Error initializing print mutex"), 1);
	if (init_forks(data))
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (error_msg("Error initializing forks"), 1);
	}
	return (0);
}
