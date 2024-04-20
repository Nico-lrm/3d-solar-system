#include "RenderTarget.hpp"

namespace SPN
{
    RenderTarget::RenderTarget(const std::unique_ptr<Window>& window)
    {
        std::string main_dir{ "C:/Users/lormi/Documents/PROJET_LORMIER_21502501/" };
        //std::string main_dir{ "" };

        this->_size = glm::dvec2(window->getWidth(), window->getHeight());
        
        // Préparation du quad pour le dessin
        std::vector<float> quadVertices {
             // positions  // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

        this->_vao = std::make_unique<VertexArray>();
        this->_vbo = std::make_unique<VertexBufferDouble>(quadVertices);

        this->_vao->Bind();
        this->_vbo->Bind();

        this->_vbo->AttachData();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); 
        glEnableVertexAttribArray(1);

        this->_vao->Unbind();
        this->_vbo->Unbind();        

        // Préparation du FrameBuffer pour le rendu de la scène
        this->_renderbuffer = std::make_unique<RenderBuffer>(window->getWidth(), window->getHeight());
        this->_render_framebuffer = std::make_unique<RenderFrameBuffer>(window->getWidth(), window->getHeight(), this->_renderbuffer->getID());
        this->_render_shader = std::make_unique<Shader>(main_dir + "assets/shader/fbo.vert",main_dir + "assets/shader/fbo.frag");

        // Préparation du BloomFramebuffer pour les effets de lumières
        this->_bloom_framebuffer = std::make_unique<BloomFrameBuffer>(window->getWidth(), window->getHeight());
        this->_downscale_shader = std::make_unique<Shader>(main_dir + "assets/shader/fbo.vert",main_dir + "assets/shader/downscaling.frag");
        this->_upscale_shader = std::make_unique<Shader>(main_dir + "assets/shader/fbo.vert",main_dir + "assets/shader/upscaling.frag");
    }

    void RenderTarget::Bind()
    {
        this->_render_framebuffer->Bind();
    }

    void RenderTarget::Unbind()
    {
        this->_render_framebuffer->Unbind();
    }

    void RenderTarget::Draw(const std::unique_ptr<UserInterface>& user_interface, const std::unique_ptr<Scene>& scene)
    {
        Blur(0.005f);  
        glDisable(GL_DEPTH_TEST);

        this->_render_shader->Bind();

        glActiveTexture(GL_TEXTURE0);
        this->_render_framebuffer->getRenderTexture()->Bind();
        this->_render_shader->setInt("render_texture", 0);

        glActiveTexture(GL_TEXTURE1);
        this->_bloom_framebuffer->getBloomTexture()->Bind();
        this->_render_shader->setInt("bright_texture", 1);

        this->_vao->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
        this->_vao->Unbind();
        
        this->_bloom_framebuffer->getBloomTexture()->Unbind();
        this->_render_framebuffer->getRenderTexture()->Unbind();
        this->_render_shader->Unbind();

        // L'interface est dessiné après, dans le RenderTarget
        user_interface->Update();
        user_interface->DrawElements(scene);
        user_interface->Render();

        glEnable(GL_DEPTH_TEST);
    }

    void RenderTarget::Blur(const float& radius)
    {
        this->_bloom_framebuffer->Bind();
        Downscale();
        Upscale(radius);
        this->_bloom_framebuffer->Unbind();
        glViewport(0, 0, this->_size.x, this->_size.y);
    }

    void RenderTarget::Downscale()
    {
        // Récupérer la chaîne de mipmap
        const auto mip_chain{ this->_bloom_framebuffer->getMipChain() };

        // Activer le shader et donner la résolution initiale à celui-ci
        this->_downscale_shader->Bind();
        this->_downscale_shader->setVec2("srcResolution", this->_size);
        
        // Utiliser la texture du RenderFramebuffer
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->_render_framebuffer->getRenderTexture()->getID());
        this->_downscale_shader->setInt("srcTexture", 0);

        // Pour chaque mipmap, on dessine la texture pour appliquer 
        for(unsigned int i = 0; i < mip_chain.size(); i++)
        {
            auto& mip{ mip_chain.at(i) };

            // On redimensionne le viewport et on attribue la texture actuelle au BloomFramebuffer
            glViewport(0, 0, mip.size.x, mip.size.y);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mip.texture->getID(), 0);

            // On dessine la texture avec le viewport actuelle
            this->_vao->Bind();
                glDrawArrays(GL_TRIANGLES, 0, 6);
            this->_vao->Unbind();

            // On prépare le prochain dessin en donnant la résolution et la texture actuelle pour le prochain dessin
            this->_downscale_shader->setVec2("srcResolution", mip.size);
            glBindTexture(GL_TEXTURE_2D, mip.texture->getID());
        }
        this->_downscale_shader->Unbind();
    }

    void RenderTarget::Upscale(const float& radius)
    {
        // Récupérer la chaîne de mipmap
        const auto mip_chain{ this->_bloom_framebuffer->getMipChain() };

        this->_upscale_shader->Bind();
        this->_upscale_shader->setFloat("filterRadius", radius);

        // On modifie la manière dont le blending est fait pour l'effet de bloom
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glBlendEquation(GL_FUNC_ADD);

        // On parcourt de la plus petite résolution à la plus grande pour obtenir notre upscale
        for(unsigned int i = mip_chain.size() - 1; i > 0; i--)
        {
            // On récupère les deux mip (i & i - 1) pour écrire la texture i dans i - 1
            const auto& actual_mip{ mip_chain.at(i) };
            const auto& next_mip{ mip_chain.at(i-1) };

            // On active la texture où on va lire
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, actual_mip.texture->getID());
            this->_upscale_shader->setInt("srcTexture", 0);

            // On écrit dans la prochaine texture pour faire l'upsampling
            glViewport(0, 0, next_mip.size.x, next_mip.size.y);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, next_mip.texture->getID(), 0);

            // On dessine la texture avec le viewport actuelle
            this->_vao->Bind();
                glDrawArrays(GL_TRIANGLES, 0, 6);
            this->_vao->Unbind();
        }

        // On désactive le blending
        glDisable(GL_BLEND);
        this->_upscale_shader->Unbind();
    }
}