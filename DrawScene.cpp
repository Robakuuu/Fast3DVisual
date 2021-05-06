#include "DrawScene.h"
#include "Camera.h"
#include "Keyboard.h"
#include "text2D.hpp"
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
ShaderProgram* Scene::GetShaderProgramByName(std::string sShaderProgramName)
{
    if (sShaderProgramName == "Lambert")
    {
        return spLambert;
    }
    else if(sShaderProgramName == "LambertTextured")
    {
        return spLambertTextured;
    }
    else if (sShaderProgramName == "Constant")
    {
        return spConstant;
    }
    else if (sShaderProgramName == "Colored")
    {
        return spColored;
    }
    else if (sShaderProgramName == "Textured")
    {
        return spTextured;
    }

    return spLambert;
}
void Scene::InitDefaultTextureAndShaders(const char* sDefaultTexturePath, std::string sDefaultShaderProgramName)
{
    m_GLIntTexture = readTexture(sDefaultTexturePath);
    SetPointerToShader(GetShaderProgramByName(sDefaultShaderProgramName));
    m_pShaderProgram->use();
}
GLuint Scene::readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    std::vector<unsigned char> image;  
    unsigned width, height;   
    unsigned error = lodepng::decode(image, width, height, filename);
    std::cout << "ERROR:" << error << "\n";

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
   

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}
Scene::Scene()
{
    
    GLFWwindow* window;
    bool bglfwInitOK = true;
    bool bWindowOpened = true;
    bool bFirstStart = true;
    std::string oLastPath = "";
   

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
        initShaders();
        glfwSetDropCallback(window, DropCallback);
        InitDefaultTextureAndShaders(DEFAULT_TEXTURE_PATH,DEFAULT_SHADER);
        initText2D("Fonts/Holstein.DDS");
        //initText2D("Fonts/Fixed.dds");

        Camera oCamera(m_pShaderProgram);
        Keyboard oKeyboard;
        
        
        int iRotate = 1;
        float fRotate = 0.1;

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            oKeyboard.CheckInput(window, m_pShaderProgram);
            
            
            if (global_PathsToObjects != oLastPath)
            {
                PrepareBuffer(global_PathsToObjects.c_str());
                oLastPath = global_PathsToObjects;
                bFirstStart = false;
            }
            if (bIsAnyObject == true)
            {
                oCamera.UpdateMvp(m_pShaderProgram);
                oCamera.SetModel(glm::rotate(oCamera.GetModel(), glm::radians(fRotate), glm::vec3(0, iRotate, 0)));
                std::cout << "Model: " << iRotate << " fRotate: " << fRotate << std::endl;

                std::string s = std::to_string(fRotate);
                char const* pchar = s.c_str();  //use char const* as target type

                printText2D(pchar, 10, 500, 60);
                DrawScene();

                glfwSwapBuffers(window);
                

            }
            else
            {
                DrawBlankStart();
                glfwSwapBuffers(window);
            }   
            glfwPollEvents();
            
        }
    }

    glfwTerminate();
}

void Scene::PrepareBuffer(const char* pathToObject)
{
    ClearObjectData();
    ObjFile oObjObject(pathToObject);
    m_vec3Vertices = oObjObject.GetVertices();
    m_vec2Uv = oObjObject.GetUvs();
    m_vec3Normals = oObjObject.GetNormals();

    for (int i = 0; i < m_vec3Vertices.size(); i++)
    {
        m_vec4PreparedVertices.push_back(glm::vec4(m_vec3Vertices[i].x, m_vec3Vertices[i].y, m_vec3Vertices[i].z, 1.0));
    }
    for (int i = 0; i < m_vec3Normals.size(); i++)
    {
        m_vec4PreparedNormals.push_back(glm::vec4(m_vec3Normals[i].x, m_vec3Normals[i].y, m_vec3Normals[i].z, 0.0));
    }
    for (int i = 0; i < m_vec2Uv.size(); i++)
    {
        m_vec2PreparedUv.push_back(glm::vec2(m_vec2Uv[i].x, m_vec2Uv[i].y));
    }
    for (int index = 0; index < m_vec4PreparedVertices.size(); index++)
    {
        glm::vec4 tmp = glm::vec4(1.0, 0.0, 0.0, 1.0);
        m_vec4Colors.push_back(tmp);
    }
    bIsAnyObject = true;

   //glGenBuffers(1, &m_GLIntVertexBuffer);
   //glGenBuffers(1, &m_GLIntUvBuffer);
  // glGenBuffers(1, &m_GLIntNormalBuffer);
   //glGenBuffers(1, &m_GLIntTexture);
}
void Scene::ClearObjectData()
{
    m_vec4PreparedVertices.clear();
    m_vec4PreparedNormals.clear();
    m_vec2PreparedUv.clear();
    m_vec4Colors.clear();
}
void Scene::DrawBlankStart()
{
    glEnableVertexAttribArray(m_pShaderProgram->a("vertex"));
    glEnableVertexAttribArray(m_pShaderProgram->a("normal"));
    glEnableVertexAttribArray(m_pShaderProgram->a("texCoord0"));
    glEnableVertexAttribArray(m_pShaderProgram->a("color"));
  

    glVertexAttribPointer(m_pShaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, (void*)0);
    glVertexAttribPointer(m_pShaderProgram->a("normal"), 4, GL_FLOAT, false, 0, (void*)0);
    glVertexAttribPointer(m_pShaderProgram->a("texCoord0"), 2, GL_FLOAT, false, 0, (void*)0);
    glVertexAttribPointer(m_pShaderProgram->a("color"), 4, GL_FLOAT, false, 0, (void*)0);



    glDrawArrays(GL_TRIANGLES, 0, m_vec3Vertices.size());

    glDisableVertexAttribArray(m_pShaderProgram->a("vertex"));
    glDisableVertexAttribArray(m_pShaderProgram->a("normal"));
    glDisableVertexAttribArray(m_pShaderProgram->a("texCoord0"));
    glDisableVertexAttribArray(m_pShaderProgram->a("color"));
    glClearColor(0.1, 0.1, 0.1, 0);
}
void Scene::DrawScene()
{
    m_pShaderProgram->use();

    glEnableVertexAttribArray(m_pShaderProgram->a("vertex"));
    glEnableVertexAttribArray(m_pShaderProgram->a("normal"));
    glEnableVertexAttribArray(m_pShaderProgram->a("texCoord0"));
    glEnableVertexAttribArray(m_pShaderProgram->a("color"));

    //glBindBuffer(GL_ARRAY_BUFFER, m_GLIntVertexBuffer);
   // glBindBuffer(GL_ARRAY_BUFFER, m_GLIntNormalBuffer);
   // glBindBuffer(GL_ARRAY_BUFFER, m_GLIntUvBuffer);
   // glBindBuffer(GL_ARRAY_BUFFER, m_GLIntTexture);

    glVertexAttribPointer(m_pShaderProgram->a("vertex"), 4, GL_FLOAT, false, 0, &m_vec4PreparedVertices[0]);
    glVertexAttribPointer(m_pShaderProgram->a("normal"), 4, GL_FLOAT, false, 0, &m_vec4PreparedNormals[0]);
    glVertexAttribPointer(m_pShaderProgram->a("texCoord0"), 2, GL_FLOAT, false, 0, &m_vec2PreparedUv[0]);
    glVertexAttribPointer(m_pShaderProgram->a("color"), 4, GL_FLOAT, false, 0, &m_vec4Colors[0]);


    glUniform1i(m_pShaderProgram->u("textureMap0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_GLIntTexture);

    glUniform1i(m_pShaderProgram->u("textureMap1"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_GLIntTexture);

	glDrawArrays(GL_TRIANGLES, 0, m_vec3Vertices.size());

    glDisableVertexAttribArray(m_pShaderProgram->a("vertex"));
    glDisableVertexAttribArray(m_pShaderProgram->a("normal"));
    glDisableVertexAttribArray(m_pShaderProgram->a("texCoord0"));
    glDisableVertexAttribArray(m_pShaderProgram->a("color"));
    glClearColor(0.1, 0.1, 0.1, 0);
}
