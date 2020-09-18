#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int list(const char *archive) {
    FILE *ff = fopen(archive, "r");
    char *e = "Error";
    long int fsize, offset = 0, archsize;
    char fname[100];

    if (ff == NULL)
        perror(e);
    else {
        fseek(ff, 0, SEEK_END);
        archsize = ftell(ff);
        for(;;) {
            fseek(ff, offset, SEEK_SET);
            fread(fname, sizeof(fname), 1, ff);
            printf("%s\n", fname);
            fseek(ff, offset + 100, SEEK_SET);
            fread(&fsize, sizeof(fsize), 1, ff);
            offset = ftell(ff) + fsize;
            if (offset >= archsize) {
                break;
            }
        }
        fclose(ff);
    }
    return 0;
}

int add(const char *archive, const char *filename) {
    FILE *ff = fopen(filename, "r");
    char *e = "Error";
    long int fsize;

    if (ff == NULL)
        perror(e);
    else {
        fseek(ff, 0, SEEK_END);
        fsize = ftell(ff);
        fseek(ff, 0, SEEK_SET);

        char buff[fsize];

        fread(buff, sizeof(buff), 1, ff);
        fclose(ff);

        ff = fopen(archive, "r+");
        if (ff == NULL)
            perror(e);
        else {
            fseek(ff, 0, SEEK_END);
            fwrite(filename, 100, 1, ff);
            fwrite(&fsize, sizeof(fsize), 1, ff);
            fseek(ff, 0, SEEK_END);
            fwrite(buff, sizeof(buff), 1, ff);
            printf("File added\n");
            fclose(ff);
        }
    }
    return 0;
}

int extract(const char *archive, const char *filename) {
    FILE *ff = fopen(archive, "r");
    long int fsize = 0, offset = 0, archsize;
    char *e = "Error";
    char fname[100];

    if (ff == NULL)
        perror(e);
    else {
        fseek(ff, 0, SEEK_END);
        archsize = ftell(ff);
        fseek(ff, 0, SEEK_SET);
        for (;;) {
            fread(fname, sizeof(fname), 1, ff);
            fseek(ff, offset + 100, SEEK_SET);
            fread(&fsize, sizeof(fsize), 1, ff);
            if (filename == NULL) {
                printf("Error: No such file in the archive \n");
                exit(0);
            }
            if(strcmp(fname, filename) == 0) {
                char buff[fsize];
                fread(buff, sizeof(buff), 1, ff);
                FILE *fout = fopen(filename, "w");
                if (fout == NULL) {
                    perror(e);
                } else {
                    fwrite(buff, sizeof(buff), 1, fout);
                    printf("File extracted\n");
                    fclose(fout);
                    break;
                }
            } else { // if doesnt match
                offset = offset + fsize + 108;
                if(offset >= archsize) {
                    printf("Error: No such file in the archive \n");
                    exit(0);
                }
                fseek(ff, offset, SEEK_SET);
            }
        }
        fclose(ff);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        FILE *ff = fopen(argv[1], "w");
        fclose(ff);
    }
    else if(argc > 2) {
        if(strcmp(argv[1], "-a") == 0)
            add(argv[2], argv[3]);
        else if ((strcmp(argv[1], "-e") == 0))
            extract(argv[2], argv[3]);
        else if ((strcmp(argv[1], "-l") == 0))
            list(argv[2]);
    } else {
        printf("usage: <flag> <tar> or <tar>\n");
    }

    return 0;
}
