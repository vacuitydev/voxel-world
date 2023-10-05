#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using vec3 = glm::vec3;
struct Transform{
    vec3 position{0};
    vec3 rotation{0};
    vec3 scale{1};
    Transform(){

    }
    Transform(vec3 p, vec3 r, vec3 s):position(p),rotation(r), scale(s){

    }
    glm::mat4 Matrix(){
        glm::mat4 trans  = glm::mat4{1.0f};
        trans = glm::translate(trans, position);
        // trans = glm::rotate(trans, )
        // trans = glm::scale(trans, scale);
        return trans;
    }
};