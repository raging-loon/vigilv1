#ifndef BASE64_H
#define BASE64_H
#include <stdlib.h>
#include <stdint.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

static char * decoding_table = NULL;
static int mod_table[] = {0,2,1};

char * base64_encode(const unsigned char * data, size_t input_len, size_t * output_len);
unsigned char * base64_decode(const char * data, size_t input_len, size_t * output_len);
void build_decoding_table();
void base64_cleanup();
#endif /* BASE64_H */