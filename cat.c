#include <stdio.h>
#include <string.h>

int cat(const char *filename, const char *flag) {
    FILE *ff = NULL;
    char *e = "Error";
    char buff[255];
    int num = 1;

    ff = fopen(filename, "r");

    if (ff == NULL)
        perror(e);
    else {
        if(strcmp(flag, "-b") == 0) {
            while (fgets((buff), sizeof(buff), ff) != NULL) {
                printf("\t%i %s \n", num, buff);
                num++;
            }
            fclose(ff);
        } else {
            while (fgets((buff), sizeof(buff), ff) != NULL)
                printf("%s", buff);
            fclose(ff);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int i;
    char *flag = "\0";

    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "-b") == 0)
            flag = "-b";
    }
    for(i=1; i<argc; i++) {
        if (strcmp(argv[i], "-b") != 0)
            cat(argv[i], flag);
    }
    return 0;
}
