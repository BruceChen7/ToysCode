#include "toys_sds.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// obtain the length of sds
size_t toys_sds_len(const sds s) {
    struct sdsHdr *sh = (void *)(s - SDS_HDR_SIZE);
    return sh->len;
}

// creat a new sds string which content is specified with init
sds toys_sds_new_len(const void *init, size_t init_len) {
    struct sdsHdr *new_sds = NULL;

    if (init) {
        new_sds = malloc(SDS_HDR_SIZE + init_len + 1);
    } else {
        new_sds = calloc(SDS_HDR_SIZE + init_len + 1, 1);
    }

    if (new_sds == NULL) return NULL;

    new_sds->len = init_len;
    new_sds->free = 0;

    if (init_len && init) {
        memcpy(new_sds->buf, init, init_len);
        new_sds->buf[init_len] = '\0';
    }
    return (char *)new_sds->buf;
}

sds toys_sds_new(const char *init) {
    size_t init_len = (init == NULL) ? 0 : strlen(init);
    return toys_sds_new_len(init, strlen(init));
}

// creat an empty sds
sds toys_sds_empty(void) { return toys_sds_new_len("", 0); }

sds toys_sds_expand_size(sds s, size_t add_len) {
    struct sdsHdr *sh, *new_sh;
    sh = (void *)(s - SDS_HDR_SIZE);

    size_t free_size = toys_sds_avail(s);

    // nothing to do if there are enough size
    //
    if (free_size >= add_len) return s;

    size_t len = toys_sds_len(s);
    size_t new_len = (len + add_len);

    if (new_len < SDS_MAX_PRESIZE)
        new_len *= 2;
    else
        new_len += SDS_MAX_PRESIZE;

    new_sh = realloc(sh, new_len + SDS_HDR_SIZE + 1);

    if (new_sh == NULL) return NULL;

    new_sh->free = new_len - len;
    return new_sh->buf;
}

void toys_sds_free(sds s) {
    struct sdsHdr *sh = (void *)(s - SDS_HDR_SIZE);
    free(sh);
}

size_t toys_sds_avail(const sds s) {
    struct sdsHdr *sh = (void *)(s - SDS_HDR_SIZE);
    return sh->free;
}

sds toys_sds_cat_len(sds s, const void *t, size_t len) {
    size_t avail_len = toys_sds_avail(s);
    size_t s_len = toys_sds_len(s);
    struct sdsHdr *sh = (void *)(s - SDS_HDR_SIZE);

    if (avail_len < len) {
        s = toys_sds_expand_size(s, len);
        if (s == NULL) return NULL;
    }

    memcpy(s + s_len, t, len);

    sh->len = s_len + len;
    sh->free = avail_len - len;
    sh->buf[sh->len] = '\0';
    return (sds)sh->buf;
}

sds toys_sds_cat(sds s, const void *t) {
    return toys_sds_cat_len(s, t, strlen(t));
}

sds toys_sds_cpy_len(sds s, const void *t, size_t len) {
    struct sdsHdr *sh = (void *)(s - SDS_HDR_SIZE);
    size_t t_len = len;
    size_t s_total_len = sh->free + sh->len;

    if (s_total_len < t_len) {
        s = toys_sds_expand_size(s, t_len - s_total_len);

        if (s == NULL) return NULL;
        sh = (void *)(s - SDS_HDR_SIZE);
        s_total_len = sh->len + sh->free;
    }

    memcpy(s, t, len);
    s[len] = '\0';
    sh->len = len;
    sh->free = s_total_len - len;
    return s;
}

sds toys_sds_cpy(sds s, const void *t) {
    return toys_sds_cpy_len(s, t, strlen(t));
}
// duplicate s
sds toys_sds_dup(const sds s) { return toys_sds_new(s); }

// make the s's content is '\0'
// update s's free space
void toys_sds_clear(sds s) {
    struct sdsHdr *sh = (void *)(s - SDS_HDR_SIZE);
    sh->free = sh->len;
    sh->len = 0;
    sh->buf[0] = '\0';
}

int toys_sds_cmp(const sds s1, const sds s2) {}

// convert all the letters to upper
void toys_sds_toupper(sds s) {
    int i;
    int len = toys_sds_len(s);
    for (i = 0; i < len; i++) s[i] = toupper(s[i]);
}

void toys_sds_tolower(sds s) {
    int j;
    int len = toys_sds_len(s);
    for (j = 0; j < len; j++) s[j] = tolower(s[j]);
}

sds toys_sds_cat_snprintf(sds s, const char *fmt, ...) {
    va_list ap;
    char *t;
    va_start(ap, fmt);
    t = toys_sds_cat_vprintf(s, fmt, ap);
    va_end(ap);
    return t;
}

static sds toys_sds_cat_vprintf(sds s, const char *fmt, va_list ap) {
    va_list cpy;
    char s_buffer[1024];
    char *buf = s_buffer;
    size_t buffer_len = strlen(fmt) * 2;

    if (buffer_len > sizeof(s_buffer)) {
        buf = malloc(buffer_len);

        if (buf == NULL) return NULL;
    } else {
        buffer_len = sizeof(s_buffer);
    }

    while (1) {
        buf[buffer_len - 2] = '\0';
        va_copy(cpy, ap);
        vsnprintf(buf, buffer_len, fmt, cpy);
        va_end(cpy);

        if (buf[buffer_len - 2] != '\0') {
            if (buf != s_buffer) {
                free(buf);
                buffer_len *= 2;
                buf = malloc(buffer_len);

                if (buf == NULL) return NULL;
                continue;
            }
        }
        break;
    }

    sds t = toys_sds_cat(s, buf);

    if (buf != s_buffer) free(buf);
    return t;
}

sds toys_sds_join(char **argv, int argc, char *sep) {}
