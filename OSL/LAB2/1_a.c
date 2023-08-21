#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void Sort(char** str, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(str[i], str[j]) > 0) {
                char temp[100];
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }
        }
    }
}

void printSubdirectories(char* dir) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp = opendir(dir);
    char** fnames = NULL;
    int k = 0;
    
    if (!dp) {
        printf("Cannot open directory : %s\n", dir);
        exit(0);
    }
    chdir(dir);
    
    while ((entry = readdir(dp))) {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            fnames = realloc(fnames, (k + 1) * sizeof(char*));
            fnames[k] = malloc(strlen(entry->d_name) + 1);
            strcpy(fnames[k], entry->d_name);
            k++;
            /*If the entry is a subdirectory (S_ISDIR(statbuf.st_mode)), and it's not . or .., 
            it dynamically allocates memory for the subdirectory name in fnames and copies the name into it.*/
        }
    }
    closedir(dp);
    
    Sort(fnames, k);
    
    for (int i = 0; i < k; i++) {
        printf("%s\n", fnames[i]);
        free(fnames[i]);
    }
    free(fnames);
    
    chdir("..");
}

int main() {
    char dir[256];
    printf("Enter Directory Name : \t");
    scanf("%s", dir);
    printSubdirectories(dir);
    return 0;
}
/*Certainly, let's break down the code snippet you provided in detail:

```c
fnames = realloc(fnames, (k + 1) * sizeof(char*));
fnames[k] = malloc(strlen(entry->d_name) + 1);
strcpy(fnames[k], entry->d_name);
k++;
```

This section of code dynamically allocates memory for storing subdirectory names. Let's go through each line step by step:

1. `fnames = realloc(fnames, (k + 1) * sizeof(char*));`:
   - `fnames` is a pointer to a pointer (`char**`) that will hold the dynamically allocated array of subdirectory name strings.
   - `realloc` is used to resize the memory block pointed to by `fnames`. It takes two arguments: the existing memory block pointer 
   (`fnames`) and the new size of the memory block. Here, the new size is calculated as `(k + 1) * sizeof(char*)`, where `k` 
   represents the current number of subdirectories found.
   - `(k + 1) * sizeof(char*)` calculates the size required for an array of `char*` pointers to hold `k + 1` elements. 
   Each `char*` pointer will point to a subdirectory name.

2. `fnames[k] = malloc(strlen(entry->d_name) + 1);`:
   - This line allocates memory for storing the characters of the subdirectory name.
   - `fnames[k]` refers to the `k`-th element of the `fnames` array. This element will store the address of the dynamically 
   allocated memory block where the subdirectory name characters will be stored.
   - `malloc(strlen(entry->d_name) + 1)` allocates memory to hold the characters of the subdirectory name. 
   `strlen(entry->d_name)` calculates the length of the subdirectory name, and `+ 1` accounts for the null-terminator 
   at the end of the string.

3. `strcpy(fnames[k], entry->d_name);`:
   - `fnames[k]` is a pointer to the memory block that holds the characters of the subdirectory name.
   - `strcpy` is used to copy the subdirectory name from `entry->d_name` into the allocated memory block pointed to by `fnames[k]`.

4. `k++;`:
   - This line increments the counter `k`, which keeps track of the number of subdirectories found.

To summarize, this block of code dynamically allocates memory to store subdirectory names. It first reallocates 
memory for the `fnames` array to accommodate one more `char*` pointer, which will store the address of the dynamically 
allocated memory for a subdirectory name. Then, it allocates memory for storing the characters of the subdirectory name 
itself, copies the subdirectory name into that memory, and increments the counter `k` to 
indicate that a new subdirectory has been stored. This process is repeated for each subdirectory found in the directory 
being scanned.*/