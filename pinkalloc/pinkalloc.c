// This file is a wrapper around malloc.c, which is the upstream source file.
// It sets configuration flags and controls which symbols are exported.

#include <stddef.h>
#include <malloc.h>
#include <string.h>

void *__pink_malloc(size_t size);
void __pink_free(void *ptr);
void *__pink_realloc(void *ptr, size_t size);

void *malloc(size_t size) {
    return __pink_malloc(size);
}

void free(void *ptr) {
    __pink_free(ptr);
}

void *calloc(size_t nmemb, size_t size) {
    void*p = malloc(nmemb * size);
    if (p != NULL) {
        memset(p, 0, nmemb * size);
    }
    return p;
}

void *realloc(void *ptr, size_t size) {
    return __pink_realloc(ptr, size);
}

// Define these to satisfy musl references.
void *__libc_malloc(size_t) __attribute__((alias("malloc")));
void __libc_free(void *) __attribute__((alias("free")));
void *__libc_calloc(size_t nmemb, size_t size) __attribute__((alias("calloc")));
