#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Macro/Macro.h"


class Scene
{
public:
	Scene();
	void PrepareBuffer(const char* pathToObject);
	void DrawScene();
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

private:
	GLuint VertexArrayID;
	GLuint m_GLIntVertexBuffer;
	GLuint m_GLIntUvBuffer;
	const char* m_pcharPathToObject;
	
	std::vector< glm::vec3 > m_vec3Vertices;
	std::vector< glm::vec2 > m_vec2Uv;

};



