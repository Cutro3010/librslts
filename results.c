#include "results.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

Result rslts_create(uint8_t code, bool lock , bool verbose, const char *custom_msg, bool success, const char *file, int line){
  Result r = {0};
  r.lock = lock;
  r.result_code = code; 
  r.verbose = verbose;
  r.success = success;
  r.file = file;
  r.line = line;
  const char *source = NULL;
  switch (code) {
    case 0:  source = "Default; Code of no meaning returned."; break;
    case 1:  source = "Default true; Result returned 1"; break;
    case 2:  source = "Default error; Result returned 2"; break;
    default: source = custom_msg ? custom_msg : "Default unknown."; break;
  }
  strncpy(r.result_text, source, 63);
  r.result_text[63] = '\0';
  return r;
}

void rslts_validate(Result *res){if (!res) return;  res->validated = true;}

void rslts_unwrap(Result *res){
  if (!res) return;
  bool is_validated = res->validated;
  if(is_validated){
    printf("Result validated; Stopping unwrap process.");
  } else {
  rslts_validate(res);
    if(res->success){
      rslts_ok(res);
    } else {
      rslts_error(res);
    }
  }
}

void rslts_ok(Result *res){if (!res) return; if(res->verbose){rslts_result_print(res);}}

void rslts_error(Result *res){
  rslts_result_print(res);
  if(res->lock){
    exit(1);
  }
}

void rslts_result_print(Result *res){
  printf("--- Result  \n");
  printf("Code:           %u\n", res->result_code);
  printf("Text:           %s\n", res->result_text);
  printf("Is locked:      %s\n", res->lock ? "true" : "false");
  printf("Success:      : %s\n", res->success ? "true" : "false");
  printf("Location:      %s:%d\n", res->file, res->line);
  printf("--- End Result\n");
}

