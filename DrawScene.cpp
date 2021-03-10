#include "DrawScene.h"
#include "Camera.h"
#include "ObjFile.h"
#include <windows.h>
#include <shellapi.h>
#include <iostream>


std::string global_PathsToObjects="";

void DropCallback(GLFWwindow* window, int count, const char** paths)
{
    int i;
    for (i = 0; i < count; i++)
    {
        std::cout << "- " << paths[i] << std::endl;
    }
    global_PathsToObjects = paths[0];
}

Scene::Scene()
{
    
    GLFWwindow* window;
    bool bglfwInitOK = true;
    bool bWindowOpened = true;

    if (!glfwInit())
    {
        bglfwInitOK = false;
    }


    window = glfwCreateWindow(WINDOW_SIZE_WIDE, WINDOW_SIZE_HEIGHT, WINDOW_NAME, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        bWindowOpened = false;
    }
    if (bWindowOpened && bglfwInitOK == true)
    {
        
        bool bNewObject = false;
        bool bFirstStart = true;
        std::string oLastPath = "";

        glfwMakeContextCurrent(window);
        glewInit();
        glfwSetDropCallback(window, DropCallback);
      

        Camera oCamera(VERTEX_SHADER, FRAGMENT_SHADER);

        
        glGenBuffers(1, &m_GLIntVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_GLIntVertexBuffer);
      // glGenBuffers(1, &m_GLIntUvBuffer);
      //  glBindBuffer(GL_ARRAY_BUFFER, m_GLIntUvBuffer);
        while (!glfwWindowShouldClose(window))
        {
            if (global_PathsToObjects != oLastPath)
            {
               
                    bNewObject = true;
                
            }
            if (bNewObject == true)
            {
                PrepareBuffer(global_PathsToObjects.c_str());
                oLastPath = global_PathsToObjects;
                bNewObject = false;
                bFirstStart = false;
            }
           
            
            if(bNewObject==false)
            {
                glUniformMatrix4fv(oCamera.GetMatrixID(), 1, GL_FALSE, &oCamera.GetMvp()[0][0]);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glUseProgram(oCamera.GetProgramID());
                DrawScene();
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
			
        }
    }
    

    glfwTerminate();
}

void Scene::PrepareBuffer(const char* pathToObject)
{

    ObjFile oObjObject(pathToObject);
    m_vec3Vertices = oObjObject.GetVertices();
    m_vec2Uv = oObjObject.GetUvs();

   
  
    glBufferData(GL_ARRAY_BUFFER, m_vec3Vertices.size() * sizeof(glm::vec3), &m_vec3Vertices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, m_vec2Uv.size() * sizeof(glm::vec2), &m_vec2Uv[0], GL_STATIC_DRAW);
}
void Scene::DrawScene()
{
	glEnableVertexAttribArray(0);
   // glBindBuffer(GL_ARRAY_BUFFER, m_GLIntVertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
        (void*)0              // array buffer offset
	);
	glDrawArrays(GL_TRIANGLES, 0, m_vec3Vertices.size());
	glDisableVertexAttribArray(0);
}
