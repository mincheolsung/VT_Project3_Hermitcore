/* Copyright (c) 2017, RWTH Aachen University
 * Author(s): Daniel Krebs <github@daniel-krebs.net>
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef UHYVE_SYSCALLS_H
#define UHYVE_SYSCALLS_H

#include <unistd.h>
#include <stddef.h>

typedef enum {
	UHYVE_PORT_WRITE	= 0x499,
	UHYVE_PORT_OPEN		= 0x500,
	UHYVE_PORT_CLOSE	= 0x501,
	UHYVE_PORT_READ		= 0x502,
	UHYVE_PORT_EXIT		= 0x503,
	UHYVE_PORT_LSEEK	= 0x504,
	UHYVE_PORT_PUT		= 0x509,
	UHYVE_PORT_GET		= 0x50a
} uhyve_syscall_t;

typedef struct {
	int fd;
	const char* buf;
	size_t len;
} __attribute__((packed)) uhyve_write_t;

typedef struct {
	const char* name;
	int flags;
	int mode;
	int ret;
} __attribute__((packed)) uhyve_open_t;

typedef struct {
	int fd;
	int ret;
} __attribute__((packed)) uhyve_close_t;

typedef struct {
	int fd;
	char* buf;
	size_t len;
	ssize_t ret;
} __attribute__((packed)) uhyve_read_t;

typedef struct {
	int fd;
	off_t offset;
	int whence;
} __attribute__((packed)) uhyve_lseek_t;

typedef struct {
	char *key;
	void *value;
	size_t value_len;
	int *ret;
} __attribute__((packed)) uhyve_put_t;

typedef struct {
	char *key;
	void *value;
	size_t *value_len;
	int *ret;
} __attribute__((packed)) uhyve_get_t;
#endif // UHYVE_SYSCALLS_H
