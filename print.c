
#include <stddef.h>
#include <stdint.h>

#define WASM_MEMORY_SIZE 65536  // 64 KB for demonstration

// Simple linear memory allocator
uint32_t heap_offset = 0;
uint8_t memory1[WASM_MEMORY_SIZE];

uint32_t malloc(uint32_t size) {
    uint32_t current_offset = heap_offset;
    heap_offset += size;
    return current_offset;
}

uint32_t getHelloString() {
    const char* hello = "Hello from WebAssembly!";
    uint32_t len = strlen(hello) + 1;  // Include null terminator
    uint32_t ptr = malloc(len);
    
    memcpy((void*)ptr, hello, len);  // Copy string to memory
    return ptr;  // Return pointer to the string
}

// Simple free implementation (no-op for simplicity)
void free(uint32_t ptr) {
    // This is a no-op; we are not tracking free blocks
}

int wasm_test(unsigned char *buf, int size) {
  static const char TEST[] = "<p>Hello world</p>";
  for (int i = 0; i < sizeof(TEST); i++) {
    buf[i] = TEST[i];
  }
  return sizeof(TEST);
}

// int print_string(char *str) {
//     printf("Received string from JavaScript: %s\n", str);
// }


char firstLetter(const char* mem) {
  uint32_t length = 0;
    while (mem[length] != '\0') {
        length++;
    }
    return length;
    // if (a == NULL || *a == '\0') {
    //     return '\0';  // Return null character if input is NULL or empty
    // }
    // return a[0];  // Return the first character
}
const char* get(const char* str) {
if (compareStringsx(str, "/hello") == 0) {
       return "You said hello!";        
     }
    else if (compareStringsx(str, "/goodbye") == 0) {
      return  "You said goodbye!";      
    }
    else if (compareStringsx(str, "/foo") == 0) {
      return "You said foo!";      
        
    }
    else if (compareStringsx(str, "/bar") == 0) {
      return "You said bar!";              
    }
    else {  
      return "Unrecognized input";
        
    }

}
uint32_t wasm_engine(const char* str){
    const char* txt1 = 
      compareStringsx(str, "/hello") == 0 ? "You said hello!" :
      // compareStringsx(str, "/goodbye") == 0 ? "You said goodbye!" :
      // compareStringsx(str, "/foo") == 0 ? "foo" : 
      // compareStringsx(str, "/bar") == 0 ? "bar" :
      "Unrecognized input";
    
 
    //const char* txt = "Hello from WebAssembly!";
    uint32_t len = strlen(txt1) + 1;  // Include null terminator
    uint32_t ptr = malloc(len);
    memcpy((void*)ptr, txt1, len);  // Copy string to memory
    return ptr;  // Return pointer to the string

}

int compareStringsx(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        // Compare characters one by one
        if (*str1 != *str2) {
            return (*str1 - *str2);  // Return the difference if not equal
        }
        str1++;
        str2++;
    }
    
    // If both strings end at the same time, they are equal
    return (*str1 - *str2);
}