#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define PREFIX "keep-"

void renameFilesInDirectory(const char *directoryPath) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory using the path passed as a parameter
    dir = opendir(directoryPath);
    if (!dir) {
        perror("Unable to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check if the file name starts with the prefix
        if (strncmp(entry->d_name, PREFIX, strlen(PREFIX)) == 0) {
            // Construct the old file path
            char oldFilePath[1024];
            snprintf(oldFilePath, sizeof(oldFilePath), "%s/%s", directoryPath, entry->d_name);

            // Construct the new file name by removing the prefix
            char *newFileName = entry->d_name + strlen(PREFIX);

            // Construct the new file path
            char newFilePath[1024];
            snprintf(newFilePath, sizeof(newFilePath), "%s/%s", directoryPath, newFileName);

            // Rename the file
            if (rename(oldFilePath, newFilePath) != 0) {
                perror("Error renaming file");
            } else {
                printf("Renamed: %s -> %s\n", oldFilePath, newFilePath);
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *directoryPath = "C:/xampp/htdocs/work/tiptech/new/news";  // Change this to your directory path
    renameFilesInDirectory(directoryPath);
    return 0;
}
