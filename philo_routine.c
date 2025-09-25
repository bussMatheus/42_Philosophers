#include "./philo.h"

static void	print_status(t_philo *philo, const char *msg)
{
	t_data	*data;

	data = philo->data;
	safe_mutex_handle(&data->print_mutex, LOCK);
	if (!data->someone_died)
		printf("%ld %d %s\n", get_time() - data->start_time, philo->id, msg);
	safe_mutex_handle(&data->print_mutex, UNLOCK);
}

static void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
	ft_usleep(500, philo->data);
}

static void	eat(t_philo *philo)
{
	t_mtx *first;
	t_mtx *second;

 	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	safe_mutex_handle(first, LOCK);
	print_status(philo, "has taken a fork");
	safe_mutex_handle(second, LOCK);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	safe_mutex_handle(philo->meal_mtx, LOCK);
	philo->last_meal_u = get_time();
	philo->meals_taken++;
	safe_mutex_handle(philo->meal_mtx, UNLOCK);
	ft_usleep(philo->data->time_to_eat, philo->data);
	safe_mutex_handle(philo->left_fork, UNLOCK);
	safe_mutex_handle(philo->right_fork, UNLOCK);
}

static void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->someone_died)
	{
		think(philo);
		eat(philo);
		sleeping(philo);
	}
	return (NULL);
}
