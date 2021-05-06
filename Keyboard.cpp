#include "Keyboard.h"

ShaderProgram* Keyboard::GetShaderProgramByName(std::string sShaderProgramName)
{
    if (sShaderProgramName == "Lambert")
    {
        return spLambert;
    }
    else if (sShaderProgramName == "LambertTextured")
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
void Keyboard::CheckInput(GLFWwindow* pActualWindow, ShaderProgram* pShaderProgram)
{
    if (glfwGetKey(pActualWindow, GLFW_KEY_F1) == GLFW_PRESS) {
        pShaderProgram=GetShaderProgramByName(COLORED_SHADER);
        pShaderProgram->use();
    }
    if (glfwGetKey(pActualWindow, GLFW_KEY_F2) == GLFW_PRESS) {
        pShaderProgram = GetShaderProgramByName(LAMBERT_SHADER);
        pShaderProgram->use();
    }
    if (glfwGetKey(pActualWindow, GLFW_KEY_F3) == GLFW_PRESS) {
        pShaderProgram = GetShaderProgramByName(CONSTANT_SHADER);
        pShaderProgram->use();
    }
    if (glfwGetKey(pActualWindow, GLFW_KEY_F4) == GLFW_PRESS) {
        pShaderProgram = GetShaderProgramByName(TEXTURED_SHADER);
        pShaderProgram->use();
    }
    if (glfwGetKey(pActualWindow, GLFW_KEY_F5) == GLFW_PRESS) {
        pShaderProgram = GetShaderProgramByName(LAMBERT_TEXTURED_SHADER);
        pShaderProgram->use();
    }
}