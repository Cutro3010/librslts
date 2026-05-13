#include "results.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

Result rslts_create(uint8_t code, bool verbose, bool success, const char *custom_msg){
  Result r;
  r.result_code = code; 
  switch (code){
    case 0:
      strncpy(r.result_text, "Default; Code of no meaning returned. (Check code number.)", 64);
      break;
    case 1:
      strncpy(r.result_text, "Default true; Result returned 1", 64);
      break;
    case 2:
      strncpy(r.result_text, "Default error; Result returned 2", 64);
      break;
    default:
      if (custom_msg) { strncpy(r.result_text, custom_msg, 64); 
      } else { strncpy(r.result_text, "Default unknown, no message code provided (Check Result initialization.)", 64);}
    r.result_text[63] = '\0'; // null terminator for safety.
  }
  return r;
}

Result rslts_validate(Result res){res.validated = true; return res;}



