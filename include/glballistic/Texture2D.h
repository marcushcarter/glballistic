#pragma once
#include <glad/glad.h>

namespace gl {

    class Texture2D {
    public:
        Texture2D() = default;
        ~Texture2D() { destroy(); }

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;

        Texture2D(Texture2D&& other) noexcept { *this = std::move(other); }
        Texture2D& operator=(Texture2D&& other) noexcept {
            if (this != &other) {
                destroy();
                m_id = other.m_id;
                other.m_id = 0;
            }
            return *this;
        }

        void create(GLsizei width, GLsizei height, GLenum internalFormat, GLenum format, GLenum type, GLsizei levels = 1) {
            if (m_id) return;
            glGenTextures(1, &m_id);
            bind();
            glTexStorage2D(GL_TEXTURE_2D, levels, internalFormat, width, height);
            m_width = width;
            m_height = height;
            m_internalFormat = internalFormat;
            m_format = format;
            m_type = type;
        }

        void destroy() {
            if (!m_id) return;
            glDeleteTextures(1, &m_id);
            m_id = 0;
        }

        void bind(GLuint unit = 0) const {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, m_id);
        }

        void bindImage(GLuint unit, GLenum access = GL_READ_WRITE, GLint level = 0) const {
            glBindImageTexture(unit, m_id, level, GL_FALSE, 0, access, m_internalFormat);
        }

        void unbind(GLuint unit = 0) const {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void setData(const void* data) const {
            bind();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_format, m_type, data);
        }

        void getData(void* data) const {
            bind();
            glGetTexImage(GL_TEXTURE_2D, 0, m_format, m_type, data);
        }

        void generateMipmaps() const {
            bind();
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void setParameters(GLenum minFilter, GLenum magFilter, GLenum wrapS, GLenum wrapT) const {
            bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
        }

        GLuint id() const { return m_id; }
        GLsizei width() const { return m_width; }
        GLsizei height() const { return m_height; }

    private:
        GLuint m_id{0};
        GLsizei m_width{0}, m_height{0};
        GLenum m_internalFormat{0}, m_format{0}, m_type{0};

    };

}