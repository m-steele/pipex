// PRINT THE ENVIRONMENT
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>

int main(int ac, char **arg, char **env)
{
	int i = 0;

	printf("Environment Variables:\n");
	while (env[i] != NULL) {
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
