#ifndef RESULTS_H
#define RESULTS_H

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
Result rslts_create(uint8_t code, bool lock, bool verbose, bool success,  const char *custom_msg, const char *file, int line);

// The "Public" Macro - THIS is what users call
#define RSLTS_NEW(code, lock, verbose, success, msg) \
    rslts_create(code, lock, verbose, success, msg, __FILE__, __LINE__)

#define RSLTS_stdOK()        rslts_create(1, false, false, true,  NULL, __FILE__, __LINE__)
#define RSLTS_stdERR()       rslts_create(2, true,  true,  false, NULL,  __FILE__, __LINE__)
#define RSLTS_stdMSG(c, msg) rslts_create(c, false,  true,  false, msg,  __FILE__, __LINE__)
#define RSLTS_stdERR_CODE(c) rslts_create(c, false,  true,  false, NULL, __FILE__, __LINE__)
#define RSLTS_stdERR_LOCK(c) rslts_create(c, true,  true,  false, NULL, __FILE__, __LINE__)


void rslts_validate(Result *res);
void rslts_unwrap(Result *res);
void rslts_result_print(Result *res);
void rslts_ok(Result *res);
void rslts_error(Result *res);
bool rslts_is_ok(Result res);
bool rslts_is_err(Result res);
void rslts_ignore_lock(Result *res);
void rslts_checksum();
void rslts_auto_check();
#endif

