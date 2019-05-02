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
char *duplicateString(char *s, int times) {
 assert(s);
 assert(times > 0);
 int len = strlen(s);
 char *out = malloc(len*times);
 if (out==NULL){
     return NULL;
 }
 assert(out);
 for (int i = 0; i < times; i++) {
     strcpy(out, s);
     out = out + len;
 }
 return out-times*len;
}
