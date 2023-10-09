#pragma once
#include <gl_context/GLContext.hpp>

template<typename T>
struct type_to_format;

template<>
struct type_to_format<GLfloat> {
    static constexpr GLuint val = GL_R32F;
};
template<>
struct type_to_format<GLint> {
    static constexpr GLuint val = GL_R32I;
};
template<>
struct type_to_format<GLuint> {
    static constexpr GLuint val = GL_R32UI;
};

template <typename T>
constexpr GLuint type_to_format_v = type_to_format<T>::val;
