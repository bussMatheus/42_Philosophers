#include "./philo.h"

static int	check_numbers(int ac, char **av)
{
	long	num;
	int		i;

	i = 1;
	while (av[i])
	{
		if (ft_is_invalid_n(av[i]))
			return (1);
		num = ft_atol(av[i]);
		if ((i == 1 && num <= 0) || num < 0 || num > INT_MAX)
			return (1);
		if (ac == 6 && i == 5 && num == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_input(int ac, char **av)
{
	if (ac != 5 && ac !=6)
		return (error_msg("Invalid number of arguments"), 1);
	if (check_numbers(ac, av))
		return (error_msg("Invalid argument(s)"), 1);
	return (0);
}

