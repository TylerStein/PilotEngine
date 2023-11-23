#pragma once

#include "game_types.h"
#include <vector>

namespace Pilot {
    namespace Primitives {
        GLfloat gQuadVertices[] = {
            // positions        
            -0.5f, -0.5f, 0.0f, // bottom left
             0.5f, -0.5f, 0.0f, // bottom right
             0.5f,  0.5f, 0.0f, // top right
            -0.5f,  0.5f, 0.0f  // top left 
        };

        GLuint gQuadIndices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
    }

    RawMesh PrimitiveQuad() {
        return RawMesh{
            std::vector<GLfloat>(Primitives::gQuadVertices, Primitives::gQuadVertices + 12),
            std::vector<GLuint>(Primitives::gQuadIndices, Primitives::gQuadIndices + 6)
        };
    }
}