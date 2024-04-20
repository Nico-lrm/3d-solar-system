#include "Skybox.hpp"

namespace SPN
{
    Skybox::Skybox()
    {
        std::string main_dir{ "C:/Users/lormi/Documents/PROJET_LORMIER_21502501/" };
        //std::string main_dir{ "" };

        const std::vector<float> cubemap_vertices
        {         
           -1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

           -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };

        const std::array<std::string, 6> filepaths {
            main_dir + "assets/skybox/right.png",
            main_dir + "assets/skybox/left.png",
            main_dir + "assets/skybox/up.png",
            main_dir + "assets/skybox/down.png",
            main_dir + "assets/skybox/front.png",
            main_dir + "assets/skybox/back.png"
        };

        this->_vao = std::make_unique<VertexArray>();
        this->_vbo = std::make_unique<VertexBufferDouble>(cubemap_vertices);
        this->_texture_skybox = std::make_unique<TextureCubemap>(filepaths);
        this->_shader = std::make_unique<Shader>(main_dir + "assets/shader/skybox.vert", main_dir + "assets/shader/skybox.frag");

        this->_vao->Bind();
        this->_vbo->Bind();
        this->_vbo->AttachData();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
        glEnableVertexAttribArray(0);

        this->_vao->Unbind();
        this->_vbo->Unbind();
    }

    void Skybox::Draw(const glm::mat4& view, const glm::mat4& proj)
    {
        glDepthFunc(GL_LEQUAL);

        glm::mat4 model{ glm::mat4(1.f) };
        model = glm::translate(model, glm::vec3(0.f));

        glActiveTexture(GL_TEXTURE0);

        this->_shader->Bind();
        this->_shader->setMat4("modelviewproj", proj * view * model);
        this->_shader->setInt("texture_skybox1", 0);

        this->_vao->Bind();
        this->_texture_skybox->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        this->_vao->Unbind();
        this->_texture_skybox->Unbind();
        this->_shader->Unbind();


        glDepthFunc(GL_LESS);
    }
}