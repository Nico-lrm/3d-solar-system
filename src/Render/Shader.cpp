#include "Shader.hpp"

namespace SPN
{
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Erreur Compilation :" << type << "\n" << infoLog << "\n";
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Erreur Link :" << type << "\n" << infoLog << "\n";            
            }
        }
    }

    Shader::Shader(const LoadedShader& loaded_shader)
    {
        const char* vertexCode{ loaded_shader.v_shader_code.c_str() };
        const char* fragmentCode{ loaded_shader.f_shader_code.c_str() };
        const char* geometryCode;

        // Une fois le code recupere, on peut compiler les shaders
        unsigned int vertex{}, fragment{}, geometry{};

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // S'il y a un geometry shader
        if(loaded_shader.g_shader_code.has_value())
        {
            geometryCode = loaded_shader.g_shader_code.value().c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &geometryCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        
        // Creation du programme de shading
        this->_id = glCreateProgram();
        glAttachShader(this->_id, vertex);
        glAttachShader(this->_id, fragment);

        if(loaded_shader.g_shader_code.has_value())
            glAttachShader(this->_id, geometry);

        // On lie l'ensemble des parties
        glLinkProgram(this->_id);
        checkCompileErrors(this->_id, "PROGRAM");

        // Suppression des parties du programme, vu que le programme est cree
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(loaded_shader.g_shader_code.has_value())
            glDeleteShader(geometry);
    }

    // Charger directement le shader (isolé, pour ceux nécessaire par l'application)
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;

        // Variables pour lire les fichiers de vertex et de fragment
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // Gerer les exceptions lors de la lecture des fichiers
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::string vPath{ vertexPath };
        std::string fPath{ fragmentPath };

        // Ouverture des fichiers
        vShaderFile.open(vPath.c_str());
        fShaderFile.open(fPath.c_str());

        // On lit le contenu des fichiers qu'on stock dans les variables
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Fichiers lus - Fermeture des fichiers
        vShaderFile.close();
        fShaderFile.close();

        vertexCode =  vShaderStream.str();
        fragmentCode =  fShaderStream.str();

        // On convertit le tout en chaîne de caracteres
        const char* vShaderCode{ vertexCode.c_str() };
        const char* fShaderCode{ fragmentCode.c_str() };

        // Une fois le code recupere, on peut compiler les shaders
        unsigned int vertex, fragment;

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        
        // Creation du programme de shading
        this->_id = glCreateProgram();
        glAttachShader(this->_id, vertex);
        glAttachShader(this->_id, fragment);

        // On lie l'ensemble des parties
        glLinkProgram(this->_id);
        checkCompileErrors(this->_id, "PROGRAM");

        // Suppression des parties du programme, vu que le programme est cree
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        // Variables pour lire les fichiers de vertex et de fragment
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;

        // Gerer les exceptions lors de la lecture des fichiers
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::string vPath{ vertexPath };
        std::string fPath{ fragmentPath };
        std::string gPath{ geometryPath };

        // Ouverture des fichiers
        vShaderFile.open(vPath.c_str());
        fShaderFile.open(fPath.c_str());
        gShaderFile.open(gPath.c_str());

        // On lit le contenu des fichiers qu'on stock dans les variables
        std::stringstream vShaderStream, fShaderStream, gShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();

        // Fichiers lus - Fermeture des fichiers
        vShaderFile.close();
        fShaderFile.close();
        gShaderFile.close();

        vertexCode =  vShaderStream.str();
        fragmentCode =  fShaderStream.str();
        geometryCode =  gShaderStream.str();

        // On convertit le tout en chaîne de caracteres
        const char* vShaderCode{ vertexCode.c_str() };
        const char* fShaderCode{ fragmentCode.c_str() };
        const char* gShaderCode{ geometryCode.c_str() };

        // Une fois le code recupere, on peut compiler les shaders
        unsigned int vertex, fragment, geometry;

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // Geometry Shader
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
        
        // Creation du programme de shading
        this->_id = glCreateProgram();
        glAttachShader(this->_id, vertex);
        glAttachShader(this->_id, fragment);
        glAttachShader(this->_id, geometry);

        // On lie l'ensemble des parties
        glLinkProgram(this->_id);
        checkCompileErrors(this->_id, "PROGRAM");

        // Suppression des parties du programme, vu que le programme est cree
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteShader(geometry);
    }

    void Shader::Delete()
    {
        glDeleteProgram(this->_id);
    }

    void Shader::Bind()
    {
        glUseProgram(_id);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    void Shader::setBool(const std::string &name, bool value)
    {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(const std::string &name, float value)
    {
        glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec2(const std::string &name, const glm::vec2 &value)
    {
        glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec2(const std::string &name, float x, float y)
    {
        glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string &name, const glm::vec3 &value)
    {
        glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec3(const std::string &name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec4(const std::string &name, const glm::vec4 &value)
    {
        glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat2(const std::string &name, const glm::mat2 &mat)
    {
        glUniformMatrix2fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }
    // ------------------------------------------------------------------------
    void Shader::setMat3(const std::string &name, const glm::mat3 &mat)
    {
        glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }
    // ------------------------------------------------------------------------
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }
}