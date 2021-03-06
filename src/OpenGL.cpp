//=====================================================================
// OpenGLCppWrapper: A C++11 OpenGL 'Core' wrapper.
// Copyright 2018 Quentin Quadrat <lecrapouille@gmail.com>
//
// This file is part of OpenGLCppWrapper.
//
// OpenGLCppWrapper is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OpenGLCppWrapper.  If not, see <http://www.gnu.org/licenses/>.
//=====================================================================

#include "OpenGL.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <GL/glew.h>
#pragma GCC diagnostic pop

namespace opengl
{
  //! \return true if the OpenGL context has been created
  //! else return false (not yet created or failed during
  //! its creation).
  bool& hasCreatedContext()
  {
    static bool s_context_started = false;
    return s_context_started;
  }

  //! \param ....
  void checkError(const char *filename, uint32_t line, const char* expression)
  {
    GLenum id;
    const char* error;

    while ((id = glGetError()) != GL_NO_ERROR)
      {
        switch (id)
          {
          case GL_INVALID_OPERATION:
            error = "GL_INVALID_OPERATION";
            break;
          case GL_INVALID_ENUM:
            error = "GL_INVALID_ENUM";
            break;
          case GL_INVALID_VALUE:
            error = "GL_INVALID_VALUE";
            break;
          case GL_OUT_OF_MEMORY:
            error = "GL_OUT_OF_MEMORY";
            break;
          case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
          default:
            error = "UNKNOWN";
            break;
          }

        // Do not use directly LOG macros because it will catch this
        // filename and its line instead of the faulty file/line which
        // produced the OpenGL error.
        Logger::instance().log(&std::cerr, logger::Error,
                               "[%s::%d] Failed executing '%s'. Reason is '%s'\n",
                               filename, line, expression, error);
      }
  }
} // namespace
