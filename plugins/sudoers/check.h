/*
 * Copyright (c) 1993-1996,1998-2005, 2007-2014
 *	Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Sponsored in part by the Defense Advanced Research Projects
 * Agency (DARPA) and Air Force Research Laboratory, Air Force
 * Materiel Command, USAF, under agreement number F39502-99-1-0512.
 */

#ifndef _SUDOERS_CHECK_H
#define _SUDOERS_CHECK_H

/* Status codes for timestamp_status() */
#define TS_CURRENT		0
#define TS_OLD			1
#define TS_MISSING		2
#define TS_NOFILE		3
#define TS_ERROR		4

/*
 * Time stamps are now stored in a single file which contains multiple
 * records.  Each record starts with a 16-bit version number and a 16-bit
 * record size.  Multiple record types can coexist in the same file.
 */
#define	TS_VERSION		1

/* Time stamp entry types */
#define TS_GLOBAL		0x01
#define TS_TTY			0x02
#define TS_PPID			0x03

/* Time stamp flags */
#define TS_DISABLED		0x01	/* entry disabled */
#define TS_ANYUID		0x02	/* ignore uid, only valid in the key */

/* XXX - may also want to store uid/gid of tty device */
struct timestamp_entry {
    unsigned short version;	/* version number */
    unsigned short size;	/* entry size */
    unsigned short type;	/* TS_GLOBAL, TS_TTY, TS_PPID */
    unsigned short flags;	/* TS_DISABLED, TS_ANYUID */
    uid_t auth_uid;		/* uid to authenticate as */
    pid_t sid;			/* session ID associated with tty/ppid */
    struct timespec ts;		/* timestamp (CLOCK_MONOTONIC) */
    union {
	dev_t ttydev;		/* tty device number */
	pid_t ppid;		/* parent pid */
    } u;
};

bool  already_lectured(int status);
bool  update_timestamp(struct passwd *pw);
int   build_timestamp(struct passwd *pw);
int   timestamp_status(struct passwd *pw);

#endif /* _SUDOERS_CHECK_H */
