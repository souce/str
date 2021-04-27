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

#include "str.h"

str get_common_prefix(str i, str j){
    int min_len = str_len(i) < str_len(j) ? str_len(i) : str_len(j);
    char common_prefix[min_len];
    int k = 0;
    for(; k < min_len; k++){
        if(i[k] == j[k]){
            common_prefix[k] = i[k];
        }else{
            common_prefix[k] = '\0';
            break;
        }
    }
    return str_new(common_prefix);
}

int main(){
    str x = str_new(" one");
    printf("str:'%s'\n", x);

    char *p = str_dump(x);
    printf("%s\n", p);
    free(p);

    if(STR_OK == str_cat(&x, " two")){
        printf("str:'%s'\n", x);
    }

    if(STR_OK == str_catprintf(&x," %d %s ", 123, "three")){
        printf("str:'%s'\n", x);
    }

    if(STR_OK == str_trim(&x, " ")){
        printf("str:'%s'\n", x);
    }

    str_range(x, 4, 50);
    printf("str:'%s'\n", x);

    int count = 0;
    str *lines = str_splitlen(x, str_len(x), " ", 1, &count);
    int i = 0;
    for(; i < count; i++){
        printf("line:%s\n", lines[i]);
        str_free(lines[i]);
    }

    str i_str = str_new("apple");
    str j_str = str_new("application");
    str common_prefix = get_common_prefix(i_str, j_str);
    printf("common_prefix:%s\n", common_prefix);
    str_free(i_str);
    str_free(j_str);
    str_free(common_prefix);

    str_free(x);
    return 0;
}
