#ifndef CONFIG_H
#define CONFIG_H

#include "os.h"

struct cfg_data;

struct cfg_data* cfg_load(const char *path);

const char* cfg_get_str(struct cfg_data *cfg, const char *key);

bool cfg_get_int(struct cfg_data *cfg, const char *key, int *ret);

void cfg_release(struct cfg_data *cfg);

#endif