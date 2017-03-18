#include "buf.h"


struct buf {
	char *buf;
	uint buflen;
	uint datalen;
};

struct buf *buf_create() {
	struct buf *buf = malloc(sizeof(*buf));

	buf->buflen = 0;
	buf->buf = NULL;
	buf->datalen = 0;

	return buf;
}

void buf_release(struct buf *buf) {
	free(buf->buf);
	free(buf);
}

static void _resize(struct buf *buf, int newsize) {
	void *pnew = NULL;
	if (NULL != buf->buf) {
		pnew = realloc(buf->buf, newsize);
		if (NULL == pnew) {
			pnew = malloc(newsize);
			memcpy(pnew, buf->buf, buf->datalen);
			free(buf->buf);
		}
	}
	else {
		pnew = malloc(newsize);		
	}
	buf->buf = pnew;
	buf->buflen = newsize;
}

// 也可直接写入
void buf_write(struct buf *buf, const void *data, uint len) {
	uint newdatalen = buf->datalen + len;

	if (newdatalen > buf->buflen)
	{
		uint newsz = max(buf->buflen*2,1024);
		while(newsz < newdatalen) {
			newsz *= 2;
		}
		_resize(buf, newsz);
	}
	memcpy(buf->buf + buf->datalen, data, len);
	buf->datalen += len;
}

// 获取有效的数据
void *buf_get_data(struct buf *buf, uint *len) {
	*len = buf->datalen;
	return buf->buf;
}