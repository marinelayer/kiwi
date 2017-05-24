#include <stdint.h>

uintptr_t __env_entropy(char **envp)
{
	uintptr_t entropy = (uintptr_t)envp;
	char **e = envp;
	while (*e) {
		char *c = *e++;
		while (*c) {
			entropy = (entropy * 0xcbf29ce484222325ull) ^ *c++;
		}
	}
	return entropy;
}
