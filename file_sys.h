#ifndef FILE_SYS_H
#define FILE_SYS_H

#include "os.h"

bool file_load(const char *path, char **data, int *datalen);

// append true表示增加，否则会清空文件
bool file_save(const char *path, const char *data, int len, bool append);

bool file_mkdir(const char *path);

// error return -1
int file_get_length(FILE * f);

bool file_is_exists(const char *path, bool include_dir);

bool file_delete(const char *path);

bool file_rename(const char *dst, const char *src);

bool file_copy(const char *dst, const char *src);

#endif