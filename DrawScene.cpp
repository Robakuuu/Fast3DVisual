#include "DrawScene.h"
#include "Camera.h"
#include "ObjFile.h"



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
        
        glfwMakeContextCurrent(window);
        glewInit();
        PrepareBuffer();
        Camera oCamera(VERTEX_SHADER, FRAGMENT_SHADER);

        while (!glfwWindowShouldClose(window))
        {
			
			
			
			glUniformMatrix4fv(oCamera.GetMatrixID(), 1, GL_FALSE, &oCamera.GetMvp()[0][0]);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(oCamera.GetProgramID());
            DrawScene();
            glfwSwapBuffers(window);
            glfwPollEvents();
			
        }
    }
    

    glfwTerminate();
}

void Scene::PrepareBuffer()
{

    ObjFile oObjObject("obj1.obj");
    m_vec3Vertices = oObjObject.GetVertices();
    m_vec2Uv = oObjObject.GetUvs();


    glGenBuffers(1, &m_GLIntVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_GLIntVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vec3Vertices.size() * sizeof(glm::vec3), &m_vec3Vertices[0], GL_STATIC_DRAW);


    glGenBuffers(1, &m_GLIntUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_GLIntUvBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vec2Uv.size() * sizeof(glm::vec2), &m_vec2Uv[0], GL_STATIC_DRAW);
}
void Scene::DrawScene()
{
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_GLIntVertexBuffer);
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