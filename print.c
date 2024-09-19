
#include <stddef.h>
#include <stdint.h>

#define WASM_MEMORY_SIZE 65536 // 64 KB for demonstration

// Simple linear memory allocator
uint32_t heap_offset = 0;
uint8_t memory1[WASM_MEMORY_SIZE];

void *memcpy(void *dest, const void *src, size_t n)
{
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;
  for (size_t i = 0; i < n; i++)
  {
    d[i] = s[i];
  }
  return dest;
}
size_t strlen(const char *str)
{
  size_t len = 0;
  while (str[len] != '\0')
  {
    len++;
  }
  return len;
}
uint32_t malloc(uint32_t size)
{
  uint32_t current_offset = heap_offset;
  heap_offset += size;
  return current_offset;
}
char *concatenate(const char *str1, const char *str2, char *result)
{
  const char *p = str1;
  char *q = result;

  // Copy the first string to the result
  while (*p)
  {
    *q++ = *p++;
  }

  // Copy the second string to the result
  p = str2;
  while (*p)
  {
    *q++ = *p++;
  }

  // Null-terminate the result
  *q = '\0';

  return result;
}

char *concatenate_html_table(char *result)
{
  return "<table>\n<tr><td>Row 1, Cell 1</td><td>Row 1, Cell 2</td></tr>\n<tr><td>Row 1, Cell 1</td><td>Row 1, Cell 2</td></tr>\n</table>\n";
  const char *table_open = "<table>\n";
  // const char* rows[] = {
  //     "<tr><td>Row 1, Cell 1</td><td>Row 1, Cell 2</td></tr>\n",
  //     "<tr><td>Row 2, Cell 1</td><td>Row 2, Cell 2</td></tr>\n"
  // };
  const char *rows[] = {"asdsa"};
  size_t row_count = sizeof(rows);
  const char *table_close = "</table>\n";
  const char *p;
  char *q = result;

  // Copy the opening table tag
  p = table_open;
  while (*p)
  {
    *q++ = *p++;
  }

  // Copy each row into the result
  for (size_t i = 0; i < row_count; ++i)
  {
    p = rows[i];
    while (*p)
    {
      *q++ = *p++;
    }
  }

  // Copy the closing table tag
  p = table_close;
  while (*p)
  {
    *q++ = *p++;
  }

  // Null-terminate the result
  *q = '\0';

  return result;
}

uint32_t getHelloString()
{
  const char *hello = "Hello from WebAssembly!";
  uint32_t len = strlen(hello) + 1; // Include null terminator
  uint32_t ptr = malloc(len);

  memcpy((void *)ptr, hello, len); // Copy string to memory
  return ptr;                      // Return pointer to the string
}

// Simple free implementation (no-op for simplicity)
void free(uint32_t ptr)
{
  // This is a no-op; we are not tracking free blocks
}

int wasm_test(unsigned char *buf, int size)
{
  static const char TEST[] = "<p>Hello world</p>";
  for (int i = 0; i < sizeof(TEST); i++)
  {
    buf[i] = TEST[i];
  }
  return sizeof(TEST);
}

// int print_string(char *str) {
//     printf("Received string from JavaScript: %s\n", str);
// }

char firstLetter(const char *mem)
{
  uint32_t length = 0;
  while (mem[length] != '\0')
  {
    length++;
  }
  return length;
  // if (a == NULL || *a == '\0') {
  //     return '\0';  // Return null character if input is NULL or empty
  // }
  // return a[0];  // Return the first character
}
const char *get(const char *str)
{
  if (compareStringsx(str, "/hello") == 0)
  {
    char result[1024];
    // const char *table = concatenate_html_table(result);
    return concatenate_html_table(result);
    //return result;
    // return "You said hello!";
  }
  else if (compareStringsx(str, "/goodbye") == 0)
  {
    return "You said goodbye!";
  }
  else if (compareStringsx(str, "/foo") == 0)
  {
    return "You said foo!!!";
  }
  else if (compareStringsx(str, "/bar") == 0)
  {
    return "You said bar!";
  }
  else
  {
    return "Unrecognized input";
  }
}

// #define MAX_HTML_SIZE 1000000
// void* custom_set(void* s, int c, size_t n) {
//     unsigned char* p = (unsigned char*)s;
//     while (n--) {
//         *p++ = (unsigned char)c;
//     }
//     return s;
// }
// char* my_strcat(char* dest, const char* src) {
//     char* dest_ptr = dest;

//     // Move pointer to the end of the destination string
//     while (*dest_ptr) {
//         dest_ptr++;
//     }

//     // Copy the source string to the destination string
//     while (*src) {
//         *dest_ptr++ = *src++;
//     }

//     *dest_ptr = '\0';  // Null-terminate the result
//     return dest;
// }

// const char* generate_html_table(const char* input_data) {
//     static char html[MAX_HTML_SIZE];
//     my_memset(html, 0, sizeof(html));  // Initialize the HTML string with 0s

//     // Add table headers
//     my_strcat(html, "<table border=\"1\">\n");
//     my_strcat(html, "<tr><th>Column1</th><th>Column2</th><th>Column3</th><th>Column4</th></tr>\n");
//     for(int i=0;i<100;i++){
//         my_strcat(html, "<tr><td>1</td><td>2</td><td>3</td><td>4</td></tr>\n");
//     }

//     // Tokenize input data by rows (assuming rows are separated by '\n')
//     // char* row_data = my_strtok((char*)input_data, "\n");
//     // while (row_data != NULL) {
//     //     my_strcat(html, "<tr>");  // Start a new table row

//     //     // Tokenize the row into columns (assuming columns are separated by spaces)
//     //     char* cell_data = my_strtok(row_data, " ");
//     //     while (cell_data != NULL) {
//     //         my_strcat(html, "<td>");  // Start a new table cell
//     //         my_strcat(html, cell_data);  // Add the cell data
//     //         my_strcat(html, "</td>");  // End the table cell
//     //         cell_data = my_strtok(NULL, " ");  // Move to the next cell in the row
//     //     }

//     //     my_strcat(html, "</tr>\n");  // End the table row
//     //     row_data = my_strtok(NULL, "\n");  // Move to the next row
//     // }

//     my_strcat(html, "</table>\n");  // End the HTML table

//     return html;  // Return the generated HTML string
// }

uint32_t wasm_engine(const char *str)
{
  const char *txt1 = get(str);
  uint32_t len = strlen(txt1) + 1; // Include null terminator
  uint32_t ptr = malloc(len);
  memcpy((void *)ptr, txt1, len); // Copy string to memory
  return ptr;                     // Return pointer to the string
}

int compareStringsx(const char *str1, const char *str2)
{
  while (*str1 && *str2)
  {
    // Compare characters one by one
    if (*str1 != *str2)
    {
      return (*str1 - *str2); // Return the difference if not equal
    }
    str1++;
    str2++;
  }

  // If both strings end at the same time, they are equal
  return (*str1 - *str2);
}