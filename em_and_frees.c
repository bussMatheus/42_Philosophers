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
