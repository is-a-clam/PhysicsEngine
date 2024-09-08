#include "shader.h"

void compileShader(unsigned int shader, const std::string &type);
void linkProgram(unsigned int shaderProgram);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vShaderString, fShaderString;
    std::ifstream vShaderFile, fShaderFile;
    std::stringstream vShaderStream, fShaderStream;
    
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath); 
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vShaderString = vShaderStream.str().c_str();
        fShaderString = fShaderStream.str().c_str();		
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vShaderString.c_str();
    const char* fShaderCode = fShaderString.c_str();

    // Compile Shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    compileShader(vertexShader, "VERTEX");

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    compileShader(fragmentShader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    linkProgram(ID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setInt(const char *name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value); 
}

void Shader::setFloat(const char *name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value); 
}

void Shader::setVector3(const char *name, const glm::vec3 &value) const
{
    glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z); 
}

void Shader::setMatrix3(const char *name, const glm::mat3 &value) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value)); 
}

void Shader::setMatrix4(const char *name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value)); 
}

void compileShader(unsigned int shader, const std::string &type)
{
    int success;
    char infoLog[512];

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::" << type << "SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void linkProgram(unsigned int shaderProgram)
{
    int success;
    char infoLog[512];

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::Program::LINKING_FAILED\n" << infoLog << std::endl;
    }
}