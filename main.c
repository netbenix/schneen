#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "common/shader.h"
#include "objects/triangle.h"

GLFWwindow* initGLFW(){
    if(!glfwInit()){
        printf("Failed to init GLFW.\n");
        return 1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(800, 600, "Schneen", NULL, NULL);
    if (window == NULL){
        printf("Failed to init window.");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    if(glewInit() != GLEW_OK){
        printf("Failed to init glew.\n");
        return NULL;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

void initGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int drawTriangle(){
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "assets/TriangleVert.shader", "assets/TriangleFrag.shader");

    static const GLfloat g_vertex_buffer_data[] = {
            0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glUseProgram(programID);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    GLint posAttrib = glGetAttribLocation(programID, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                          5*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(programID, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                          5*sizeof(float), (void*)(2*sizeof(float)));

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);

}

int main(){

    glewExperimental = GL_TRUE;

    GLFWwindow *glfwWindow = initGLFW();
    initGL();

    //Main loop
    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);


        static const GLfloat g_vertex_buffer_data[] = {
                0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
        };

        //This shit does not work yet
        //Triangle tria = InitTriangle(g_vertex_buffer_data, "assets/TriangleVert.shader", "assets/TriangleFrag.shader");
        //DrawTriangle(&tria);


        drawTriangle();

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();

    }while(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(glfwWindow) == 0);


    glfwTerminate();
}