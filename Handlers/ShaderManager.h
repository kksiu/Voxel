#pragma once

#include <string>
#include <map>
#include <memory>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

class ShaderManager
{
public:
    //load and retrieve the shaders
    void loadShader(std::string fileName, std::string keyName);
    void loadGLShader(std::string fileName, std::string keyName);
    
    GLuint getGLShader(std::string keyName);
    std::shared_ptr<sf::Shader> getShader(std::string keyName);
    
    static ShaderManager& getInstance()
    {
        static ShaderManager instance;
        return instance;
    }
    
private:
    ShaderManager();
    ~ShaderManager();
    std::map<std::string, GLuint> mGLShaders;
    std::map<std::string, std::shared_ptr<sf::Shader>> mSFMLShaders;
    
    //used http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/ for a function to load a shader
    GLuint loadGLShaderHelper(std::string vert, std::string);
    std::string readFile(const char* filePath);
};
