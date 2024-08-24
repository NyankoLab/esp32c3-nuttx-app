/****************************************************************************
 * apps/netutils/webserver/httpd.h
 *
 *   Copyright (C) 2007, 2009, 2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Based on uIP which also has a BSD style license:
 *
 *   Author: Adam Dunkels <adam@sics.se>
 *   Copyright (c) 2001-2005, Adam Dunkels.
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef _NETUTILS_WEBSERVER_HTTPD_H
#define _NETUTILS_WEBSERVER_HTTPD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <nuttx/net/netconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HTTPD_IOBUFFER_SIZE (3*MIN_TCP_MSS)

/* This is the maximum size of a file path */

#ifndef CONFIG_NETUTILS_HTTPD_MAXPATH
#  define CONFIG_NETUTILS_HTTPD_MAXPATH PATH_MAX
#endif

#define HTTPD_MAX_FILENAME CONFIG_NETUTILS_HTTPD_MAXPATH

/* Other tunable values.  If you need to change these values, please create
 * new configurations in apps/netutils/webserver/Kconfig
 */

#define HTTPD_MAX_CONTENTLEN  32
#define HTTPD_MAX_HEADERLEN   220
#define HTTPD_MAX_CHUNKEDLEN  16

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct httpd_fs_file
{
  FAR char *data;
  int len;
#if defined(CONFIG_NETUTILS_HTTPD_MMAP) || \
    defined(CONFIG_NETUTILS_HTTPD_SENDFILE)
  int fd;
#endif
#ifdef CONFIG_NETUTILS_HTTPD_SENDFILE
  char path[PATH_MAX];
#endif
};

struct httpd_state
{
  char ht_buffer[HTTPD_IOBUFFER_SIZE];  /* recv() buffer */
  char ht_filename[HTTPD_MAX_FILENAME]; /* filename from GET command */
#ifndef CONFIG_NETUTILS_HTTPD_KEEPALIVE_DISABLE
  bool ht_keepalive;                    /* Connection: keep-alive */
#endif
#if defined(CONFIG_NETUTILS_HTTPD_ENABLE_CHUNKED_ENCODING)
  bool ht_chunked;                      /* Server uses chunked encoding for tx */
#endif
  struct httpd_fs_file ht_file;         /* Fake file data to send */
  int ht_sockfd;                        /* The socket descriptor from accept() */
  FAR char *ht_scriptptr;
  uint16_t ht_scriptlen;
  uint16_t ht_sndlen;
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

int httpd_open(const char *name, struct httpd_fs_file *file);
int httpd_openindex(struct httpd_state *pstate);
int httpd_close(struct httpd_fs_file *file);
int httpd_senderror(struct httpd_state *pstate, int status);
int httpd_sendfile(struct httpd_state *pstate);
int httpd_parse(struct httpd_state *pstate);
int httpd_send_datachunk(int sockfd, void *data, int len, bool chunked);
int httpd_send_headers(struct httpd_state *pstate, int status, int len);

/* 'file' must be allocated by caller and will be filled in by the function. */

#if defined(CONFIG_NETUTILS_HTTPD_SENDFILE)

int httpd_sendfile_open(const char *name, struct httpd_fs_file *file);
int httpd_sendfile_close(struct httpd_fs_file *file);
int httpd_sendfile_send(int outfd, struct httpd_fs_file *file);

#elif defined(CONFIG_NETUTILS_HTTPD_MMAP)

int  httpd_mmap_open(const char *name, struct httpd_fs_file *file);
int  httpd_mmap_close(struct httpd_fs_file *file);

#else

int  httpd_fs_open(const char *name, struct httpd_fs_file *file);
void httpd_fs_init(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* _NETUTILS_WEBSERVER_HTTPD_H */
