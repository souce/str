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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sds.h"
#include "str.h"

/* 
 * Duplicate a str as char pointer.
 * 
 * Example: 
 *     str s = str_new("Hello World");
 *     char *p = str_dump(s);
 *     printf("%s\n", p); => "Hello World" 
 *     free(p);
 */
char *str_dump(const str s){
    size_t l = str_len(s) + 1; //including the terminating null byte ('\0')
    char *p = (char *)calloc(1, l);
    memcpy(p, s, l);
    return p;
}

/* 
 * Create a new str with the content specified by the 'init' pointer and 'initlen'.
 * If NULL is used for 'init' the string is initialized with zero bytes.
 * 
 * Example: 
 *     str s = str_newlen("Hello World", 5);
 *     printf("%s\n", s); => "Hello" 
 */
str str_newlen(const void *init, size_t initlen){
    return sdsnewlen(init, initlen);
}

/* 
 * Create a new str starting from a null terminated C string.
 * 
 * Example: 
 *     str s = str_new("Hello World");
 *     printf("%s\n", s); => "Hello World" 
 */
str str_new(const char *init){
    return sdsnew(init);
}

/*
 * Create an empty (zero length) str.
 * 
 * Example: 
 *     str s = str_empty();
 *     printf("%zu\n", str_len(s)); => 0
 */
str str_empty(){
    return sdsempty();
}

/*
 * Calculates the length of the str s, excluding the terminating null byte ('\0'). 
 * 
 * Example: 
 *     str s = str_new("Hello World");
 *     printf("%zu\n", str_len(s)); => 11
 */
size_t str_len(const str s){
    return sdslen(s);
}

/*
 * Checks if a str contains string.
 * 
 * Example: 
 *     str s = str_new("Hello World");
 *     str_is_empty(s); => false
 * 
 *     str s1 = NULL;
 *     str_is_empty(s1); => true
 * 
 *     str s2 = str_empty();
 *     str_is_empty(s2); => true
 */
int str_is_empty(const str s){
    if(NULL == s){
        return 1;
    }
    return 0 == str_len(s);
}

/*
 * Duplicate a str.
 * 
 * Example: 
 *     str s1 = str_new("Hello World");
 *     str s2 = str_dup(s1);
 *     str_free(s1);
 *     str_free(s2); //'s2' is not 's1'
 */
str str_dup(const str s){
    return sdsdup(s);
}

/*
 * Free a str.
 */
void str_free(str s){
    sdsfree(s);
}

/* 
 * copies the string pointed to by t, including the terminating null byte ('\0'), 
 * to the str pointed to by s.
 * 
 * Example: 
 *     str s = str_new("Hello World");
 *     str_cpy(s, "World");
 *     printf("%s\n", s); => "World"
 */
str str_cpy(sds s, const char *t){
    return sdscpy(s, t);
}

/*
 * Split 's' with separator in 'sep'. 
 * An array of str strings is returned. 
 * *count will be set by reference to the number of tokens returned. 
 * 
 * Example: 
 *     char *s = "a b c d";
 *     int count = 0;
 *     str *lines = str_splitlen(s, str_len(x), " ", 1, &count);
 *     int i = 0;
 *     for(; i < count; i++){
 *         printf("line:%s\n", lines[i]);
 *     }
 *     str_freesplitres(lines, count);
 */
str *str_splitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count){
    return sdssplitlen(s, len, sep, seplen, count);
}

/*
 * Free the result returned by sdssplitlen(), or do nothing if 'tokens' is NULL.
 * 
 * Example:
 *     str *lines = str_splitlen(...);
 *     str_freesplitres(lines, count);
 * 
 * Warning:
 *     str *lines = str_splitlen(...);
 *     int i = 0;
 *     for(; i < count; i++){
 *         str_free(lines[i]); //Don't do that!!!
 *     }
 */
void str_freesplitres(sds *tokens, int count){
    sdsfreesplitres(tokens, count);
}

/*
 * Turn the string into a smaller (or equal) string containing 
 * only the substring specified by the 'start' and 'end' indexes.
 *
 * start and end can be negative, where -1 means the last character of the string, 
 * -2 the penultimate character, and so forth.
 * 
 * Example: 
 *     str s = str_new("Hello World");
 *     str_range(s, 1, -1);
 *     printf("%s\n", s); => "ello World"
 */
void str_range(sds s, ssize_t start, ssize_t end){
    sdsrange(s, start, end);
}

#define STR_SAFE(func,str,...) \
({ \
    int __res = STR_ERR; \
    if(NULL != (str)){ \
        sds __tmp = (func)((str), ## __VA_ARGS__); \
        if(NULL != __tmp){ \
            (str) = __tmp; \
            __res = STR_OK; \
        } \
    } \
    __res; \
})

/* 
 * Appends the 't' string to the 's' str, overwriting the terminating null byte ('\0') at the end of dest, 
 * and then adds a terminating null byte.
 * 
 * Example: 
 *     str s = str_new("Hello");
 *     if(STR_OK == str_cat(&s, " World"))
 *         printf("str:'%s'\n", x); => "Hello World"
 */
int str_cat(str *s, const char *t){
    return STR_SAFE(sdscat, *s, t);
}

/* 
 * Append the specified binary-safe string pointed by 't' of 'len' bytes to the
 * end of the specified sds string 's'.
 * 
 * Example: 
 *     str s = str_new("Hello");
 *     if(STR_OK == str_catlen(&s, " World", 6))
 *         printf("str:'%s'\n", x); => "Hello World"
 */
int str_catlen(str *s, const char *t, size_t len){
    return STR_SAFE(sdscatlen, *s, t, len);
}

/* 
 * Remove the part of the string from left and from right composed just of
 * contiguous characters found in 'cset', that is a null terminted C string.
 * 
 * Example:
 *     str s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
 *     if(STR_OK == str_trim(s, "Aa. :"))
 *         printf("%s\n", s); => "HelloWorld"
 */
int str_trim(str *s, const char *cset){
    return STR_SAFE(sdstrim, *s, cset);
}

/* 
 * Formats a series of characters and appends to the str buffer.
 * 
 * Example: 
 *     str s = str_new("Hello");
 *     if(STR_OK == str_catprintf(&s," %d %s", 123, "World"))
 *         printf("%s\n", s); => "Hello 123 World"
 */
int str_catprintf(str *s, const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    int res = STR_SAFE(sdscatvprintf, *s, fmt, ap);
    va_end(ap);
    return res;
}

/*
 * Like str_catprintf() but gets va_list instead of being variadic.
 */
int str_catvprintf(str *s, const char *fmt, va_list ap){
    return STR_SAFE(sdscatvprintf, *s, fmt, ap);
}
