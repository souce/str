/*
 * 
 * Copyright (c) 2021, Joel
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __STR_H_
#define __STR_H_
#ifdef __cplusplus
extern "C" {
#endif
    
    #include "sds.h"

    #define STR_OK 0
    #define STR_ERR -1
        
    typedef sds str;

    //safe
    char *str_dump(const str s);
    str str_newlen(const void *init, size_t initlen);
    str str_new(const char *init);
    str str_new(const char *init);
    str str_empty();
    size_t str_len(const str s);
    int str_is_empty(const str s);
    str str_dup(const str s);
    void str_free(str s);
    str str_cpy(str s, const char *t);
    str *str_splitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count);
    void str_freesplitres(sds *tokens, int count);
    void str_range(str s, ssize_t start, ssize_t end);

    //unsafe
    int str_cat(str *s, const char *t);
    int str_catlen(str *s, const char *t, size_t len);
    int str_trim(str *s, const char *cset);
    int str_catprintf(str *s, const char *fmt, ...);
    int str_catvprintf(str *s, const char *fmt, va_list ap);

#ifdef __cplusplus
}
#endif
#endif
