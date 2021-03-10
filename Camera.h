#pragma once
#include "DrawScene.h"

class Camera
{
public:
	Camera(const char* oVertexShaderPath, const char* oFragmentShaderPath);
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

	void SetProgramID(GLuint GLuIProgramID) { m_GLuIProgramID = GLuIProgramID; };
	GLuint GetProgramID() { return m_GLuIProgramID; };

	void SetMatrixID(GLuint GLuIMatrixID) { m_GLuIMatrixID = GLuIMatrixID; };
	GLuint GetMatrixID() { return m_GLuIMatrixID; };

	void SetProjection(glm::mat4 mat4Projection) { m_mat4Projection = mat4Projection; };
	glm::mat4 GetProjection() { return m_mat4Projection; };

	void SetView(glm::mat4 mat4View) { m_mat4View = mat4View; };
	glm::mat4 GetView() { return m_mat4View; };

	void SetModel(glm::mat4 mat4Model) { m_mat4Model = mat4Model; };
	glm::mat4 GetModel() { return m_mat4Model; };

	glm::mat4 GetMvp() { return m_mat4Mvp; };


private:
	GLuint m_GLuIProgramID;
	glm::mat4 m_mat4Projection;
	glm::mat4 m_mat4View;
	glm::mat4 m_mat4Model;
	glm::mat4 m_mat4Mvp = m_mat4Projection * m_mat4View * m_mat4Model;
	GLuint m_GLuIMatrixID;
};