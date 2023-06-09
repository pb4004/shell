#include <stdio.h> // remove later
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#ifndef BUFSIZE
#define BUFSIZE 128
#endif
static char buf[BUFSIZE];
static unsigned pos;
static unsigned bytes;
static int closed;
static int input;

// isspace but \n is not whitespace
int is_space(char c) {
    if (c == '\n') return 0;
    return isspace(c);
}

void words_init(int fd) {
    input = fd;
    pos = 0;
    bytes = 0;
    closed = 0;
}

char *words_next(void) {
    if (closed)
        return NULL;
        
    // skip whitespace
    while (1) {
        // ensure we have a char to read
        if (pos == bytes) {
            bytes = read(input, buf, BUFSIZE);
            if (bytes < 1) {
                closed = 1;
                return NULL;
            }
            pos = 0;
        }
        if (!is_space(buf[pos]))
            break;
        ++pos;
    }

    // start reading a word
    int start = pos;
    char *word = NULL;
    int wordlen = 0;
    do {
        ++pos;
        if (pos == bytes) {
            // save word so far
            int fraglen = pos - start;
            word = realloc(word, wordlen + fraglen + 1);
            memcpy(word + wordlen, buf + start, fraglen);
            wordlen += fraglen;
            if (buf[pos-1] == '\n' || buf[pos-1] == '<' || buf[pos-1] == '>' || buf[pos-1] == '|') {
                word[wordlen] = '\0';
                return word;    
            }
            // refresh the buffer
            bytes = read(input, buf, BUFSIZE);
            if (bytes < 1) {
                closed = 1;
                break;
            }
            pos = 0;
            start = 0;
        } else if (buf[pos-1] == '\n' || buf[pos-1] == '<' || buf[pos-1] == '>' || buf[pos-1] == '|') {
            int fraglen = pos - start;
            word = realloc(word, wordlen + fraglen + 1);
            memcpy(word + wordlen, buf + start, fraglen);
            wordlen += fraglen;
            word[wordlen] = '\0';
            return word;    
        }
    } while (!is_space(buf[pos]));

    // grab the word from the current buffer
    // (Note: start == pos if we refreshed the buffer and got a space first.)
    if (start < pos) {
        int fraglen = pos - start;
        word = realloc(word, wordlen + fraglen + 1);
        memcpy(word + wordlen, buf + start, fraglen);
        wordlen += fraglen;
    }

    if (word) {
        word[wordlen] = '\0';
    }

    return word;
}