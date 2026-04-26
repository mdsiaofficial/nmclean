#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

//! Helper to remove a directory and all its contents (like rm -rf)
static void remove_recursive_internal(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (lstat(full_path, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                remove_recursive_internal(full_path);
            } else {
                unlink(full_path);
            }
        }
    }
    closedir(dir);
    rmdir(path);
}

void remove_recursive(const char *path) {
    remove_recursive_internal(path);
    printf("Deleting: %s\n", path);
}

//! Main traversal function
void find_and_delete_node_modules(const char *base_path) {
    struct dirent *entry;
    DIR *dir = opendir(base_path);

    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        //! Skip current/parent and all hidden directories (dot folders)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.')
            continue;

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

        struct stat statbuf;
        if (lstat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, "node_modules") == 0) {
                remove_recursive(path);
            } else {
                // Keep searching deeper
                find_and_delete_node_modules(path);
            }
        }
    }
    closedir(dir);
}

int main() {
    printf("Scanning for node_modules in current directory...\n");
    find_and_delete_node_modules(".");
    printf("Clean-up complete.\n");
    return 0;
}
