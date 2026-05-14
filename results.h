#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t result_code;
    char result_text[64];
    bool lock;      
    bool success;
    bool verbose;
    bool validated; 
    const char *file; // Added
    int line;        // Added
} Result;

// The "Private" function
Result rslts_create(uint8_t code, bool lock, bool verbose, bool success, const char *custom_msg, const char *file, int line);

// The "Public" Macro - THIS is what users call
#define RSLTS_NEW(code, lock, verbose, success, msg) \
    rslts_create(code, lock, verbose, success, msg, __FILE__, __LINE__)

void rslts_validate(Result *res);
void rslts_unwrap(Result *res);
void rslts_result_print(Result *res);
void rslts_ok(Result *res);
void rslts_error(Result *res);

#endif
