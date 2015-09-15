// See also
// https://github.com/angrave/SystemProgramming/wiki/File-System%2C-Part-4%3A-Working-with-directories
#include <sys/stat.h>

#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fix my code!

int search(char*path) {
    DIR *dir;
    struct dirent *dp;
    if ((dir = opendir (path)) == NULL) {
        perror ("Cannot open path");
        return 1;
    }
    // Create a symlink for testing purposes
    // We don't care if this fails because testdir already exists
    // This is the same as the shell command ln -s . testdir
    symlink(".","testdir");    

    while ((dp = readdir (dir)) != NULL) {
         char newpath[ strlen(path) + strlen(dp->d_name) + 2];
        sprintf(newpath,"%s/%s" , path,dp->d_name);
        printf("%s ",newpath);
        struct stat s;
        if( stat(newpath, &s) !=0 ) {
            printf("? %s", strerror(errno));
            continue;
        }
        if(S_ISLNK(dp->d_ino)) {
            char buf[1024];
            ssize_t n =
                readlink(newpath,  buf, sizeof(buf) -1);
            if(n >=0) {
                buf[n]= '\0';
                printf("-> %s", buf);
            }
        }

        else if(S_ISDIR(dp->d_ino)) {
            puts("(is dir)");
            search(newpath);
        }
        else printf("size:%lu inode:%ld", s.st_size, dp->d_ino);

    }
    closedir(dir);
    return 0;
}

int main(int argc, char**argv) {
    if(argc != 2 ) {
        fprintf(stderr,"Usage: %s dir\nPrints the contents of the directory and all subdirectories (symlinks are not followed)",argv[0]);
        exit(1);
    }
    return search(argv[1]);
}