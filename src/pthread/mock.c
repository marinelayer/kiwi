#include <signal.h>
#include <pthread.h>

int pthread_mutex_init(pthread_mutex_t *m, const pthread_mutexattr_t *attr) { return 0; }
int pthread_mutex_destroy(pthread_mutex_t *m) { return 0; }
int pthread_mutex_lock(pthread_mutex_t *m) { return 0; }
int pthread_mutex_unlock(pthread_mutex_t *m) { return 0; }
int pthread_mutex_trylock(pthread_mutex_t *m) { return 0; }
int pthread_sigmask(int how, const sigset_t * restrict set, sigset_t * restrict oset) { return 0; }
