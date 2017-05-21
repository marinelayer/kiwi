int *__errno_location(void)
{
	//return &__pthread_self()->errno_val;
	static int errno_val;
	return &errno_val;
}
