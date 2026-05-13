#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool success;
    uint8_t result_code;
    char result_text[64];
    bool validated; // a result is validated the moment it is shown after creation.
} Result;

Result rslts_create(uint8_t result_code, bool verbose, bool success, const char *custom_msg);
Result rslts_validate(Result res);

#endif
