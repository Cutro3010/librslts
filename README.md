# librslts
Simple C library that handles results of operations. 

A small idea I had and wanted to make.
My first C project.

# Features

* Simple `Result` structure
* Macros for fast result creation
* Built-in success/error helpers
* Automatic source location (`__FILE__`, `__LINE__`)
* Runtime validation system
* Fatal error locking
* Global checksum integrity verification

---

# Installation

Include the files in your project:

```c
#include "results.h"
```

Compile with:

```bash
gcc main.c results.c -o app
```

---

# Result Structure

```c
typedef struct {
    uint8_t result_code;
    char result_text[64];

    bool lock;
    bool success;
    bool verbose;
    bool validated;

    const char *file;
    int line;
} Result;
```

---

# Creating Results

## Standard Success

```c
Result r = RSLTS_stdOK();
```

Creates:

* success = true
* code = 1
* non verbose
* non locked

---

## Standard Error

```c
Result r = RSLTS_stdERR();
```

Creates:

* success = false
* verbose = true
* locked = true

---

## Custom Error Message

```c
Result r = rslts_stdMSG(10, "Database connection failed");
```

---

## Generic Result Creation

```c
Result r = RSLTS_NEW(
    50,         // code
    false,      // lock
    true,       // verbose
    false,      // success
    "Custom error"
);
```

---

# Automatic Debug Location

Every macro automatically stores:

```c
__FILE__
__LINE__
```

This allows precise debugging output.

Example:

```txt
Location: main.c:42
```

---

# Unwrapping Results

Use:

```c
rslts_unwrap(&result);
```

Behavior:

* Validates the result
* If success:

  * optionally prints if verbose
* If error:

  * prints automatically
  * exits if locked

---

# Validation System

Each result should be validated.

```c
rslts_validate(&result);
```

The library tracks:

* total created results
* total validated results

---

# Checksum System

At the end of the program:

```c
rslts_checksum();
```

The library checks:

```txt
Results created == Results validated
```

If not:

```txt
[WARNING] RSLTS Checksum Failed!
```

---

# Printing Results

```c
rslts_result_print(&result);
```

Example output:

```txt
--- Result
Code:           2
Text:           Default error; Result returned 2
Is locked:      true
Success:        false
Location:       main.c:18
--- End Result
```

---

# Utility Functions

## Check Success

```c
if (rslts_is_ok(result)) {
    // success
}
```

---

## Check Error

```c
if (rslts_is_err(result)) {
    // error
}
```

---

## Ignore Lock

Prevents automatic `exit(1)`.

```c
rslts_ignore_lock(&result);
```

---

# Example

```c
#include "results.h"

int main() {

    Result ok = RSLTS_stdOK();
    rslts_unwrap(&ok);

    Result err = rslts_stdMSG(
        99,
        "Something went wrong"
    );

    rslts_ignore_lock(&err);

    rslts_unwrap(&err);

    rslts_checksum();

    return 0;
}
```

---

# Notes

## Locked Results

If `lock == true`, the program terminates:

```c
exit(1);
```

after printing the error.

---

## Verbose Results

If `verbose == true`, successful results are printed automatically.

---

# Possible Improvements

* idk
* Colored terminal output (sounds cool)
