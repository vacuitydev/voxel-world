#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <vector>

using namespace glm;
struct VertexData{
    vec3 position{0};
    vec3 color{0};
    vec2 uv{0};
    VertexData(vec3 _p,vec3 _c, vec2 _uv):position(_p),color(_c),uv(_uv){

    }
    VertexData(vec3 _p):position(_p){
        
    }
    std::string to_string(){
        return fmt::format("Position: {}, {}, {}; Color: {}, {}, {}; UV: {}, {}", 
        position.x,position.y,position.z,
        color.r,color.g,color.b,
        uv.x,uv.y);
    }
    std::vector<float> to_vec_float(){
        return std::vector<float>{position.x,position.y, position.z, color.x,color.y,color.z, uv.x,uv.y};
    }
};