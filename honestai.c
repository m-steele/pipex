#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fd1[2];
	pid_t pid; // Use pid_t for process IDs

	if (pipe(fd1) == -1) // Create the pipe ONCE
	{
		perror("pipe failed");
		return (1); // Or exit(EXIT_FAILURE)
	}

	pid = fork();

	if (pid < 0) // Always check for fork failure
	{
		perror("fork failed");
		close(fd1[0]); // Clean up pipe ends before exiting
		close(fd1[1]);
		exit(EXIT_FAILURE);
	}

	if (pid > 0) // Parent Process (Producer: ls -l)
	{
		dup2(fd1[1], STDOUT_FILENO); // Redirect parent's stdout to pipe's write-end
		close(fd1[0]);               // Parent closes read-end of pipe (it won't read from it)
		close(fd1[1]);               // Parent closes original write-end (STDOUT_FILENO is now the reference)

		execlp("ls", "ls", "-l", NULL); // Parent attempts to become "ls -l"

		// --- Code below is ONLY reached if execlp for "ls" FAILS ---
		perror("execlp ls failed in parent");
		// Parent failed to become "ls". It should wait for the child it spawned
		// before exiting, to prevent the child from becoming a zombie.
		int status;
		waitpid(pid, &status, 0); // Correct place to wait IF parent's execlp fails
		exit(EXIT_FAILURE);       // Parent exits with failure status
	}
	else // pid == 0: Child Process (Consumer: sort -r)
	{
		dup2(fd1[0], STDIN_FILENO);  // Redirect child's stdin from pipe's read-end
		close(fd1[0]);               // Child closes original read-end (STDIN_FILENO is now the reference)
		close(fd1[1]);               // Child closes write-end of pipe (it won't write to it - CRUCIAL for EOF)

		execlp("sort", "sort", "-r", NULL); // Child attempts to become "sort -r"

		// --- Code below is ONLY reached if execlp for "sort" FAILS ---
		perror("execlp sort failed in child");
		exit(EXIT_FAILURE); // Child exits with failure status
	}

	// This part of main is effectively unreachable if both parent and child
	// either successfully execlp or exit due to execlp failure.
	// If it were reachable, it would imply a logic error above.
	// For safety, one might close fds here if there was a path, but it's cleaner
	// to ensure all paths above handle their fds and exit.
	// return (0); // Also likely unreachable. The parent/child paths dictate exit.
}