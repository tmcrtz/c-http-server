#ifndef RETURNCODE_H
#define RETURNCODE_H

char* return_code(int status_code, char* file, char* file_content);
char* content_type_getter(char* file);
void sent_file_getter(int* status_code, char** code_definition, char** sent_file);

#endif