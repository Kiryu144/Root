/* Created by David Klostermann on 01.06.2017. */
#ifndef ROOT_BASICMESH_H
#define ROOT_BASICMESH_H

#include <GLM/common.hpp>
#include <vector>

namespace standardmesh {

static const glm::vec3 ___model_cube_face_front[] = {
        //FRONT, left bottom
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0),
        //FRONT, right top
        glm::vec3(0, 1, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(1, 0, 0)
};

static const glm::vec3 ___model_cube_face_front_normal[] = {
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1)
};

static const glm::vec3 ___model_cube_face_right[] = {
        //RIGHT, left bottom
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 1),
        glm::vec3(1, 1, 0),
        //RIGHT, right top
        glm::vec3(1, 0, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(1, 1, 0)
};

static const glm::vec3 ___model_cube_face_right_normal[] = {
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0)
};

static const glm::vec3 ___model_cube_face_left[] = {
        //LEFT, left bottom
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 1),
        //LEFT, right top
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 1)
};

static const glm::vec3 ___model_cube_face_left_normal[] = {
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0)
};

static const glm::vec3 ___model_cube_face_back[] = {
        //BACK, left bottom
        glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 1),
        glm::vec3(0, 1, 1),
        //BACK, right top
        glm::vec3(0, 1, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(1, 0, 1)
};

static const glm::vec3 ___model_cube_face_back_normal[] = {
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1)
};

static const glm::vec3 ___model_cube_face_top[] = {
        //TOP, left bottom
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 1),
        glm::vec3(1, 1, 0),
        //TOP, right top
        glm::vec3(1, 1, 0),
        glm::vec3(1, 1, 1),
        glm::vec3(0, 1, 1)
};

static const glm::vec3 ___model_cube_face_top_normal[] = {
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0)
};

static const glm::vec3 ___model_cube_face_bottom[] = {
        //BOTTOM, left bottom
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 0, 1),
        //BOTTOM, right top
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 1),
        glm::vec3(0, 0, 1)
};

static const glm::vec3 ___model_cube_face_bottom_normal[] = {
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0)
};


static const glm::vec3 ___model_cube[] = {
        //FRONT, left bottom
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0),
        //FRONT, right top
        glm::vec3(0, 1, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(1, 0, 0),

        //RIGHT, left bottom
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 1),
        glm::vec3(1, 1, 0),
        //RIGHT, right top
        glm::vec3(1, 0, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(1, 1, 0),

        //LEFT, left bottom
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 1),
        //LEFT, right top
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 1),

        //BACK, left bottom
        glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 1),
        glm::vec3(0, 1, 1),
        //BACK, right top
        glm::vec3(0, 1, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(1, 0, 1),

        //TOP, left bottom
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 1),
        glm::vec3(1, 1, 0),
        //TOP, right top
        glm::vec3(1, 1, 0),
        glm::vec3(1, 1, 1),
        glm::vec3(0, 1, 1),

        //BOTTOM, left bottom
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 0, 1),
        //BOTTOM, right top
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 1),
        glm::vec3(0, 0, 1),
};

static const glm::vec3 ___model_plane[] = {
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0),

        glm::vec3(0, 1, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(1, 0, 0)
};

static const glm::vec2 ___model_plane_uv[] = {
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(0, 1),

        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0)
};

static std::vector<glm::vec3> model_cube(___model_cube, ___model_cube + sizeof(___model_cube) / sizeof(glm::vec3));
//static std::vector<glm::vec2> model_cube_uv(___model_cube_uv, ___model_cube_uv + sizeof(___model_cube_uv) / sizeof(glm::vec2));

static std::vector<glm::vec3> model_cube_front(___model_cube_face_front, ___model_cube_face_front + sizeof(___model_cube_face_front) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_right(___model_cube_face_right, ___model_cube_face_right + sizeof(___model_cube_face_right) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_left(___model_cube_face_left, ___model_cube_face_left + sizeof(___model_cube_face_left) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_back(___model_cube_face_back, ___model_cube_face_back + sizeof(___model_cube_face_back) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_top(___model_cube_face_top, ___model_cube_face_top + sizeof(___model_cube_face_top) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_bottom(___model_cube_face_bottom, ___model_cube_face_bottom + sizeof(___model_cube_face_bottom) / sizeof(glm::vec3));

static std::vector<glm::vec3> model_cube_front_normal(___model_cube_face_front_normal, ___model_cube_face_front_normal + sizeof(___model_cube_face_front_normal) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_right_normal(___model_cube_face_right_normal, ___model_cube_face_right_normal + sizeof(___model_cube_face_right_normal) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_left_normal(___model_cube_face_left_normal, ___model_cube_face_left_normal + sizeof(___model_cube_face_left_normal) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_back_normal(___model_cube_face_back_normal, ___model_cube_face_back_normal + sizeof(___model_cube_face_back_normal) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_top_normal(___model_cube_face_top_normal, ___model_cube_face_top_normal + sizeof(___model_cube_face_top_normal) / sizeof(glm::vec3));
static std::vector<glm::vec3> model_cube_bottom_normal(___model_cube_face_bottom_normal, ___model_cube_face_bottom_normal + sizeof(___model_cube_face_bottom_normal) / sizeof(glm::vec3));

static std::vector<glm::vec3> model_plane(___model_plane, ___model_plane + sizeof(___model_plane) / sizeof(glm::vec3));
static std::vector<glm::vec2> model_plane_uv(___model_plane_uv, ___model_plane_uv + sizeof(___model_plane_uv) / sizeof(glm::vec2));

}

#endif
