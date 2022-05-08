#include <string.h>

#include "triangle.h"
#include "../common/shader.h"

Triangle InitTriangle(const GLfloat *newVertData, char *vertShader, char *fragShader){
    Triangle tria;

    tria.vertData = newVertData;
    tria.vertShader = vertShader;
    tria.fragShader = fragShader;

    glGenVertexArrays(1, &tria.vertArrID);
    glBindVertexArray(tria.vertArrID);

    tria.programID = LoadShaders(tria.vertShader, tria.fragShader);

    glGenBuffers(1, &tria.vertBuf);
    glBindBuffer(GL_ARRAY_BUFFER, tria.vertBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tria.vertData), tria.vertData, GL_STATIC_DRAW);

    return tria;
}

void DrawTriangle(Triangle *tria){
    glUseProgram(tria->programID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, tria->vertBuf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    GLint posAttrib = glGetAttribLocation(tria->programID, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                          5*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(tria->programID, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                          5*sizeof(float), (void*)(2*sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

}

void DeleteTriangle(Triangle *tria){
    glDeleteBuffers(1, &tria->vertBuf);
    glDeleteVertexArrays(1, &tria->vertArrID);
    glDeleteProgram(tria->programID);
}