/* Created by David Klostermann on 28.06.2017. */
#ifndef ROOT_RENDER_H
#define ROOT_RENDER_H

#include <amethyst>

namespace Render{
    struct RenderData { //Nothing but vertices
        AM::VBO<glm::vec3, 3> vertices;
    };

    struct URenderData : public RenderData { //Vertices + UV data
        AM::VBO<glm::vec2, 2> uv;
    };

    struct NRenderData : public RenderData { //Vertices + Normal data
        AM::VBO<glm::vec3, 3> normal;
    };

    struct UNRenderData : public URenderData, public NRenderData { //Vertices + UV data + Normal data

    };


}


#endif
