#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    unsigned int ID;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    
    void use();
    
    void setInt(const char *name, int value) const;   
    void setFloat(const char *name, float value) const;
    void setVector3(const char *name, const glm::vec3 &value) const;
    void setMatrix3(const char *name, const glm::mat3 &value) const;
    void setMatrix4(const char *name, const glm::mat4 &value) const;
};
  
#endif