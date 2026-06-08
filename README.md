*This project has been created as part of the 42 curriculum by fabde-ar.*

# Get Next Line

## Description

Get Next Line is a C function that reads and returns one line at a time from a file descriptor. Each successive call returns the next line from the same file descriptor, including the terminating `\n` character (except for the last line if the file does not end with `\n`). When there is nothing left to read or an error occurs, the function returns `NULL`.

The project introduces two key concepts in C programming: **static variables** for maintaining state between function calls, and **file descriptor management** for reading from files and standard input.

The bonus part extends the function to handle **multiple file descriptors simultaneously**, allowing interleaved reading from different sources without losing track of each descriptor's reading position.

## Instructions

### Compilation

The project does not include a Makefile. Compile with the `-D BUFFER_SIZE=n` flag to define the read buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

If compiled without the `-D BUFFER_SIZE` flag, a default value of 10 is used.

For the bonus part:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

The caller is responsible for freeing the returned line after use.

### Files

**Mandatory:** `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`

**Bonus:** `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`

## Algorithm

### Approach

The algorithm uses a **static variable** (`storage_box`) to persist unprocessed data between calls. The reading process is compartmentalized into a helper function (`ft_search_newline`) that handles the read loop, separated from the main function to comply with the 42 Norm's 25-line limit per function.

### Flow

1. **Validation** — reject invalid file descriptors (negative or exceeding system limits) and invalid `BUFFER_SIZE` values.

2. **Read loop** (`ft_search_newline`) — read `BUFFER_SIZE` bytes at a time into a temporary buffer, concatenate with the accumulated content in the static variable using `ft_strjoin`, and repeat until a `\n` is found or EOF is reached. Error handling cleans up the static variable on `read()` failure or `malloc` failure.

3. **Line extraction** — locate the `\n` position using `ft_strchr` and pointer arithmetic. Extract the line (including `\n`) with `ft_substr`. Update the static variable to contain only the remainder after `\n`.

4. **EOF handling** — when no `\n` is found and `read()` returns 0, the remaining content is returned as the final line. Subsequent calls return `NULL`.

### Bonus: Multiple File Descriptors

The bonus replaces `static char *storage_box` with `static char *storage_box[MAX_FD]`, where `MAX_FD` defaults to 1024. Each file descriptor uses its own array slot (`storage_box[fd]`), enabling independent reading from multiple sources. The helper functions remain unchanged since they already operate via `char **` (pointer to pointer), receiving `&storage_box[fd]` instead of `&storage_box`.

### Complexity Analysis

The current implementation has **O(n²)** time complexity for lines of length `n`, caused by `ft_strjoin` re-copying all accumulated content at every read iteration. For a line of `n` bytes with `BUFFER_SIZE` of `b`, the total bytes copied are approximately `n²/2b`. This is acceptable for typical text files but becomes a bottleneck for very large single-line files (e.g., 20000+ characters).

An **O(n)** alternative would replace the repeated string concatenation with a linked list of read buffers, combining them into a single string only once per line. This approach would require replacing `ft_strjoin` with linked list operations (`ft_lstnew`, `ft_lstadd_back`, `ft_lst_combine`). Analysis confirmed this fits within the 42 Norm constraints (5 functions per file, 3 files), but the significant refactoring effort was deemed disproportionate to the gain for this project's scope. The O(n²) solution was retained as a conscious engineering trade-off.

### Helper Functions

All helper functions are reimplemented in `get_next_line_utils.c` (the project forbids using libft):

- `ft_strlen` — string length calculation
- `ft_strchr` — locate first occurrence of a character
- `ft_strjoin` — concatenate two strings into a new allocation
- `ft_substr` — extract a substring from a given position and length

## Project Structure

```
get_next_line/
├── get_next_line.c              # Main function and read loop helper
├── get_next_line_utils.c        # Helper functions (strlen, strchr, strjoin, substr)
├── get_next_line.h              # Header with prototypes and BUFFER_SIZE default
├── get_next_line_bonus.c        # Bonus: multiple file descriptor support
├── get_next_line_utils_bonus.c  # Bonus: helper functions (identical to mandatory)
├── get_next_line_bonus.h        # Bonus: header with MAX_FD definition
└── README.md
```

## Resources

### References

- `man 2 read` — Linux manual page for the `read()` system call
- `man 2 open` — Linux manual page for `open()` and file descriptors
- 42 Norm v4 — coding standard and constraints

### AI Usage

AI (Claude, by Anthropic) was used as a **study and discussion partner** throughout the project, following a guided-learning methodology:

- **Concept study** — understanding file descriptors, `read()`, static variables, buffer management, and algorithmic complexity (Big O notation) through structured discussion
- **Code review** — identifying bugs, memory leaks, and Norm violations in code written by the student
- **Debugging guidance** — diagnosing segfaults and test failures through reasoning and analysis (e.g., `NULL_CHECK` failures, `const` correctness, pointer arithmetic)
- **Architecture discussion** — evaluating trade-offs between O(n²) and O(n) approaches, feasibility within Norm constraints

AI was **not** used to generate the implementation. All code was written by the student based on conceptual understanding built through discussion.

## Author

**Fábio Araújo** - [@fabde-ar](https://github.com/fabde-ar)

Developed as part of **42 Porto** curriculum.
