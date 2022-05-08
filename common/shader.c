#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glew.h>

#include "shader.h"

char* GetFileContent(const char *filePath){
    char* content;
    int contentSize;

    FILE* file = fopen(filePath, "r");

    if(file == NULL){
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    contentSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    content = malloc(contentSize+1);
    size_t fileEOF = fread(content, 1, contentSize, file);
    content[fileEOF] = 0;

    return content;
}

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path){
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    char const *vertextShaderCode = GetFileContent(vertex_file_path);
    char const *fragmentShaderCode = GetFileContent(fragment_file_path);

    glShaderSource(vertexShaderID, 1, &vertextShaderCode, NULL);
    glCompileShader(vertexShaderID);

    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderID);

    //Nope, no error logging stuff.

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);


    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;

}