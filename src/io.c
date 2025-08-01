#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <libgen.h>

FILE *fopen_rel(const char *filename, const char *mode) {
	char exe_path[PATH_MAX];
	ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);

	if (len <= 0) {
		fprintf(stderr, "some stuff happend, so couldnt open readlink\n");
		return NULL;
	}
	if (len >= PATH_MAX) {
		fprintf(stderr,  "Unfortunately absolute path to executable is too long, consider making it shorter\n");
		return NULL;
	}

	exe_path[len] = 0;

	char *exe_dir = dirname(exe_path);

	char file_abs_path[PATH_MAX];
	snprintf(file_abs_path, sizeof(char) * PATH_MAX, "%s/%s", exe_dir, filename);

	return fopen(file_abs_path, mode);
}
