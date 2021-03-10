#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
	void PrepareBuffer();
	void DrawScene();
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

private:
	GLuint VertexArrayID;
	GLuint m_GLIntVertexBuffer;
	GLuint m_GLIntUvBuffer;
	
	std::vector< glm::vec3 > m_vec3Vertices;
	std::vector< glm::vec2 > m_vec2Uv;

};



