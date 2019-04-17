#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

char *stringDuplicator();

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    char* test="hello";
    //stringDuplicator("hello",3);
    printf("%s\n",stringDuplicator(test,3));
    printf("%s\n", test);

 return 0;
}

//Convention Error 3: Lack of spaces
char *stringDuplicator(const char *s, int times) { // Convention Error 1 + 2: Use of Const in function and wrong variable name s instead of str
 assert(s); // Compilation Error 1:  Wrong use of !
 assert(times > 0);
 int LEN = strlen(s); // Convention Error 3: variable name with capital letters
 char *out = malloc(sizeof(char)*LEN*times); // Convention Error 3: sizeof(char) in malloc
 if (out==NULL){ // Compilation Error 2: Return Null in case of fail to malloc
     return NULL;
 }
 assert(out); // Replaced with IF
 for (int i = 0; i < times; i++) {
     strcpy(out, s); // Compilation Error 3: Change the order of strcpy & out commands
     out = out + LEN;
 }
 return out-times*LEN; // Compilation Error 4: Return the finish of the string instead of the beginning
}
