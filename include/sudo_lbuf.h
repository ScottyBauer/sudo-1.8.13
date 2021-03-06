/*
 * Copyright (c) 2007, 2010, 2011, 2013, 2014
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
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SUDO_LBUF_H
#define _SUDO_LBUF_H

/*
 * Line buffer struct.
 */
struct sudo_lbuf {
    int (*output)(const char *);
    char *buf;
    const char *continuation;
    int indent;
    int len;
    int size;
    int cols;
};

typedef int (*sudo_lbuf_output_t)(const char *);

__dso_public void sudo_lbuf_init_v1(struct sudo_lbuf *lbuf, sudo_lbuf_output_t output, int indent, const char *continuation, int cols);
__dso_public void sudo_lbuf_destroy_v1(struct sudo_lbuf *lbuf);
__dso_public void sudo_lbuf_append_v1(struct sudo_lbuf *lbuf, const char *fmt, ...) __printflike(2, 3);
__dso_public void sudo_lbuf_append_quoted_v1(struct sudo_lbuf *lbuf, const char *set, const char *fmt, ...) __printflike(3, 4);
__dso_public void sudo_lbuf_print_v1(struct sudo_lbuf *lbuf);

#define sudo_lbuf_init(_a, _b, _c, _d, _e) sudo_lbuf_init_v1((_a), (_b), (_c), (_d), (_e))
#define sudo_lbuf_destroy(_a) sudo_lbuf_destroy_v1((_a))
#define sudo_lbuf_append sudo_lbuf_append_v1
#define sudo_lbuf_append_quoted sudo_lbuf_append_quoted_v1
#define sudo_lbuf_print(_a) sudo_lbuf_print_v1((_a))

#endif /* _SUDO_LBUF_H */
