#pragma once

#include <cstddef>
#include <gl_context/ShaderProgram.hpp>
#include <gl_context/Texture.hpp>
#include "TypeToFormat.hpp"

template<size_t VBO_COUNT, typename ProgramConfig>
struct ComputeShaderBase {
    struct ImageBuffer {
        GLuint id;
        Texture tex;
        GLuint access;
        GLuint format;
        void init(ArrayBufferObject& vbo, GLuint id, GLuint access, GLuint format) {
            this->id = id;
            this->access = access;
            this->format = format;
            tex.bind<GL_TEXTURE_BUFFER>().tex_buffer(vbo, format);
        }
        void bind() {
            tex.bind_image(id, access, format);
        }
    };

    std::array<ImageBuffer, VBO_COUNT> image_buffers;
    ShaderProgram program;
    template<typename T>
    void set_buffer(ArrayBufferObject& vbo, GLuint id, GLuint access) {
        image_buffers.at(id).init(vbo, id, access, type_to_format_v<T>);
    }
    void bind_buffer_images() {
        for(auto& ib : image_buffers) {
            ib.bind();
        }
    }
    ComputeShaderBase(const std::string& code)
        : program(Shader(code, GL_COMPUTE_SHADER)) {}

    ProgramConfig use_program() {
        return {program.use()};
    }
    void dispatch(GLuint x, GLuint y, GLuint z) {
        bind_buffer_images();
        glDispatchCompute(x, y, z);
    }
    void barrier() {
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }
};
