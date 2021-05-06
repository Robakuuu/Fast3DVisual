#pragma once
#include "DrawScene.h"
class Keyboard  {
	std::string m_sActuallyPressedKey;
public:
	ShaderProgram* GetShaderProgramByName(std::string sShaderProgramName);
	void CheckInput(GLFWwindow* pActualWindow, ShaderProgram* pShaderProgram);
};