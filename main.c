#include "./philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_valid_input(argc, argv))
		return (1);
	if (init_data(argc, argv, &data))
		return (1);
	if (run(&data))
		return (destroy_data(&data), 1);
	destroy_data(&data);
	return (0);
}
