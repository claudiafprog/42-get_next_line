*This project has been created as part of the 42 curriculum by clferrei.*

# Get Next Line

## Description

Get Next Line is a C project that implements a function which reads a line from a file descriptor.

The function returns one line at a time on each call, including the terminating `\n` when present. When there is nothing left to read or an error occurs, it returns `NULL`.

The project focuses on understanding:
- static variables
- buffered input using `read()`
- memory management in C
- handling partial reads from file descriptors

---

## Functionality

- Reads from a file descriptor incrementally
- Returns one full line per call
- Preserves state between calls using a static stash
- Handles files with or without trailing `\n`
- Works with different `BUFFER_SIZE` values
- Supports standard input (`stdin`)
- Bonus: supports multiple file descriptors simultaneously

---

## Compilation

Compile using:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=n *.c
```
Example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```
The project must compile with different BUFFER_SIZE values.

Run the executable:

```bash
./a.out
```
---

## Usage

The repository includes optional test mains inside the source files.

To test the project:
- Uncomment the provided `main` function in the desired file
- Compile normally with the required flags

These test mains are intended for local testing and debugging purposes and can be removed or ignored during evaluation.

---

## Algorithm 

The implementation uses a persistent buffer (stash) to store unread data between function calls.

Each call performs the following steps:

- Read data from the file descriptor into a temporary buffer
- Append the data to the existing stash
- Search for a newline character
- Extract a complete line from the stash
- Update the stash with remaining content
``` id="k1q9xt"

This process ensures that only the necessary amount of data is read per call.

---

## Bonus

The bonus implementation extends the mandatory part by:

Supporting multiple file descriptors at the same time
Using a static array of stashes indexed by file descriptor

This allows switching between file descriptors without losing reading state.

---

## Resources

```md id="p3z8aa"
- 42 subject documentation (Get Next Line)
- man 2 read
- man 3 malloc
- man 3 free
``` id="t7m2nb"

---

## AI Usage

```md id="x8k2dv"
AI tools were used to:

- review edge cases
- help validate memory management logic
- improve clarity of documentation
``` id="q9lm3c"

All implementation decisions and code were developed manually.

---

## Notes
No use of lseek()
No global variables (except allowed static usage)
Memory is dynamically allocated and must be freed by the caller
Designed to handle different buffer sizes efficiently
