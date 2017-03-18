#ifndef buf_h
#define buf_h

#include "os.h"

struct buf;

struct buf *buf_create();

void buf_release(struct buf *buf);

// 也可直接写入
void buf_write(struct buf *buf, const void *data, uint len);

// 获取有效的数据
void *buf_get_data(struct buf *buf, uint *len);

#endif