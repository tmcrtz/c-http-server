#include "../../include/server.h"
// maybe change return to void and just use return_code within
void return_file(char* file_name, int sock_accept) 
{
    char path[512];

    if (strcmp(file_name, "/") == 0) {
        strcpy(path, "../src/frontend/front_page.html");
    }

    else {
        // add "/" to end of directory if missing
        char fixed_name[256];
        if (file_name[0] == '/')
            strcpy(fixed_name, file_name);

        else {
            fixed_name[0] = '/';
            strcpy(fixed_name + 1, file_name);
        }
        snprintf(path, sizeof(path), "../src/frontend%s", fixed_name);
    }

    char *file_content = open_file(path);
    if (!file_content) {
        printf("open_file failed for %s\n", path);
        char *not_found = return_code(404, path, ""); //404 already handled so no need to pass any content
        send(sock_accept, not_found, strlen(not_found), 0);
        free(not_found);
        return;
    }

    char *response = return_code(200, path, file_content);
    send(sock_accept, response, strlen(response), 0);

    free(file_content);
    free(response);
}

char* open_file(char* file_dir) 
{
    FILE *fptr = fopen(file_dir, "rb");
    if (!fptr)
    {
        printf("fopen fail\n");
        return NULL;
    }



    if (fseek(fptr, 0, SEEK_END) != 0) 
    {
        fclose(fptr);
        return NULL;
    }

    long size = ftell(fptr);

    if (size < 0) 
    {
        fclose(fptr);
        return NULL;
    }

    if (fseek(fptr, 0, SEEK_SET) != 0 ) 
    {
        fclose(fptr);
        return NULL;
    }

    char* buf = malloc(size + 1);
    fread(buf, 1, size, fptr);
    buf[size] = 0;

    fclose(fptr);

    return buf;

}


