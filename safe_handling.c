#include "./philo.h"

static int	handle_mtx_error(int status, t_opc opcode)
{
	if (!status)
		return (0);
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_msg("The value specified by the mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		error_msg("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_msg("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (EPERM == status)
		error_msg("The current thread does not hold a lock on a mutex.");
	else if (ENOMEM == status)
		error_msg("The proccess can't allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		error_msg("Mutex is Locked");
	return (1);
}

int	safe_mutex_handle(t_mtx *mtx, t_opc opcode)
{
	int	status;

	status = 0;
	if (INIT == opcode)
		status = pthread_mutex_init(mtx, NULL);
	else if (LOCK == opcode)
		status = pthread_mutex_lock(mtx);
	else if (UNLOCK == opcode)
		status = pthread_mutex_unlock(mtx);
	else if (DESTROY == opcode)
		status = pthread_mutex_destroy(mtx);
	return (handle_mtx_error(status, opcode));
}
