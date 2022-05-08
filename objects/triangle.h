#ifndef SCHNEEN_TRIANGLE_H
#define SCHNEEN_TRIANGLE_H

#include <GL/glew.h>

typedef struct {
    const GLfloat *vertData;
    GLuint vertBuf;
    GLuint vertArrID;
    char *vertShader;
    char *fragShader;
    GLuint programID;
} Triangle;

Triangle InitTriangle(const GLfloat *newVertData, char *vertShader, char *fragShader);
void DrawTriangle(Triangle *tria);
void DeleteTriangle(Triangle *tria);

#endif //SCHNEEN_TRIANGLE_H
