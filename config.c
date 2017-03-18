#include "config.h"
#include "pubfunc.h"
#include "debug_malloc.h"

struct cfg_node {
	char *key;
	char *str;
};

struct cfg_data {
	struct cfg_node *node;
	int size;
	int bufsize;
};

static void _cfg_resize(struct cfg_data *cfg, int newsize) {
	struct cfg_node *n = malloc(newsize*sizeof(*n));
	memcpy(n, cfg->node, cfg->size*sizeof(*n));
	free(cfg->node);

	cfg->node = n;
	cfg->bufsize = newsize;
}

static void _cfg_add(struct cfg_data *cfg, const char *key, const char *str) {
	if (cfg->size >= cfg->bufsize) {
		_cfg_resize(cfg, cfg->bufsize * 2);
	}
	struct cfg_node *cur = cfg->node + cfg->size;

	cur->key = _strdup(key);
	cur->str = _strdup(str);

	trim(cur->key);
	trim(cur->str);

	++cfg->size;
}

struct cfg_data* cfg_load(const char *path) {
	int len = 0;
	char *pdata = NULL;
	if (!file_load(path, &pdata, &len)) {
		return NULL;
	}

	struct cfg_data *cfg = malloc(sizeof(*cfg));
	cfg->bufsize = 32;
	cfg->node = malloc(cfg->bufsize*sizeof(*cfg->node));
	cfg->size = 0;	

	char buf[1024];
	int prolen = 0;
	while (prolen < len) {
		if (!get_line(pdata, len, &prolen, buf, sizeof(buf)))
		{
			break;
		}
		trim(buf);
		if (buf[0] == '#')
		{
			continue;
		}
		struct split_list *list = split_string(buf, '=');
		int sz = split_get_size(list);
		if (sz >= 2) {
			_cfg_add(cfg, split_get(list, 0), split_get(list, 1));
		}
		split_free(list);
	}
	free(pdata);
	
	return cfg;
}

const char* cfg_get_str(struct cfg_data *cfg, const char *key) {
	int i;
	for (i = 0; i < cfg->size; ++i) {
		if (strcmp(cfg->node[i].key, key) == 0) {
			return cfg->node[i].str;
		}
	}
	return NULL;
}

bool cfg_get_int(struct cfg_data *cfg, const char *key, int *ret) {
	const char *data = cfg_get_str(cfg, key);
	if (NULL != data) {
		*ret = atoi(data);
		return true;
	}
	return false;
}

void cfg_release(struct cfg_data *cfg) {
	int i;
	for (i = 0; i < cfg->size; ++i) {
		free(cfg->node[i].key);
		free(cfg->node[i].str);
	}
	free(cfg->node);
	free(cfg);
}