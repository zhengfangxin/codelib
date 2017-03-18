#include "file_sys.h"
#include <sys/stat.h>
#include "debug_malloc.h"


#ifndef S_ISDIR
#define S_ISDIR(mode)   (((mode) & S_IFMT) == S_IFDIR)
#endif

bool file_load(const char *path, char **data, int *datalen) {
	*datalen = 0;
	*data = NULL;

	FILE * f = NULL;
#ifdef _WINDOWS
	fopen_s(&f, path, "rb");
#else
	f = fopen(path, "rb");
#endif

	if (f == NULL)
	{
		return false;
	}
	
	int len = file_get_length(f);
	if (len < 0) {
		fclose(f);
		return false;
	}

	bool error = false;
	char *buf = NULL;
	if (len > 0)
	{
		buf = malloc(len + 4);
		if (buf != NULL)
		{
			size_t r;
			r = fread(buf, len, 1, f);
			if (r != 1) {
				error = true;
			}
		}
		else {
			printf("memory out\n");
		}
	}
	fclose(f);

	if (error)
	{
		free(buf);
		return false;
	}
	if (len > 0) {
		memset(buf + len, 0, 4); // set end zero
	}

	*datalen = len;
	*data = buf;

	return true;
}

bool file_save(const char *path, const char *data, int len, bool append) {
	FILE * f = NULL;
	if (append)
	{
		f = fopen(path, "ab");
	}
	else
	{
		f = fopen(path, "wb");
	}
	if (f == NULL)
	{
		return false;
	}
	bool suc = true;
	if (len > 0)
	{
		size_t r = fwrite(data, len, 1, f);
		if (r != 1)
		{
			suc = false;
		}
	}

	fclose(f);
	return suc;
}

int file_get_length(FILE * f)
{
	int cur = ftell(f);
	if (cur < 0) {
		return -1;
	}

	int r = fseek(f, 0, SEEK_END);
	if (r != 0) {
		return -1;
	}

	int len = ftell(f);

	r = fseek(f, cur, SEEK_SET);
	if (r != 0) {
		return -1;
	}

	if (len < 0) {
		return -1;
	}
	return len;
}

bool file_mkdir(const char *path) {
#ifdef _WINDOWS
	return _mkdir(path) == 0;
#else
	umask(0);
	return mkdir(path, 0777) == 0;
#endif
}

bool file_is_exists(const char *path, bool include_dir) {
	struct stat file_stat;
	int iRet = stat(path, &file_stat);
	if (0 == iRet)
	{
		if (!include_dir && S_ISDIR(file_stat.st_mode)) {
			return false;
		}
		return true;
	}
	return false;
}

bool file_delete(const char *path) {
#ifdef _WINDOWS
	return _unlink(path) == 0;
#else
	return unlink(path) == 0;
#endif
}

bool file_rename(const char *dst, const char *src) {
	return rename(src, dst) == 0;
}

bool file_copy(const char *dst, const char *src) {
	int len = 0;
	char *data = NULL;
	file_load(src, &data, &len);
	bool bSuc = file_save(dst, data, len, false);
	free(data);
	return bSuc;
}