#include "./philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (check_valid_input(argc, argv))
		return (1);
	if (init_data(argc, argv, &data))
		return (1);

	return (0);
}
