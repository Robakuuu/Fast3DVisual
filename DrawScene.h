#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <lodepng.h>
#include "shaderprogram.h"
#include <stdio.h>
#include <CString>
#include <fstream>
#include <sstream>
#include <vector>
#include "Macro/Macro.h"


class Scene
{
public:
	Scene();
	GLuint readTexture(const char* filename);
	void PrepareBuffer(const char* pathToObject);
	void DrawScene();
	void DrawBlankStart();
	void ClearObjectData();
	void InitDefaultTextureAndShaders(const char* sDefaultTexturePath, std::string sDefaultShaderProgramName);
	ShaderProgram* GetShaderProgramByName(std::string sShaderProgramName);

	void SetPointerToShader(ShaderProgram* pShader) {m_pShaderProgram = pShader;};
	ShaderProgram* GetPointerToShader() {return m_pShaderProgram;};

private:
	GLuint VertexArrayID;
	GLuint m_GLIntVertexBuffer;
	GLuint m_GLIntUvBuffer;
	GLuint m_GLIntNormalBuffer;
	GLuint m_GLIntTexture;
	ShaderProgram* m_pShaderProgram;
	const char* m_pcharPathToObject;
	bool bIsAnyObject = false;
	
	std::vector< glm::vec3 > m_vec3Vertices;
	std::vector< glm::vec2 > m_vec2Uv;
	std::vector< glm::vec3 > m_vec3Normals;

	std::vector< glm::vec4 > m_vec4PreparedNormals;
	std::vector< glm::vec4 > m_vec4PreparedVertices;
	std::vector< glm::vec2 > m_vec2PreparedUv;
	std::vector< glm::vec4 > m_vec4Colors;

};



