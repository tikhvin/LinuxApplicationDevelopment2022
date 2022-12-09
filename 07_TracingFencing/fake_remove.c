#define _GNU_SOURCE

#include <dlfcn.h>
#include <string.h>

typedef int (*real_remove_t)(const char* filename);

int real_remove(const char* filename) {
	return ((real_remove_t)dlsym(RTLD_NEXT, "remove"))(filename);
}

int remove(const char* filename) {
	if (strstr(filename, "PROTECT") == NULL) {
		return real_remove(filename);
	} else {
		return 0;
	}
}
