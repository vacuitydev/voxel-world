#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "vertex_data.h"
using namespace std;
struct Coordinate
{
    float x;
    float y;
    Coordinate(float x, float y)
    {
        this->x = x;
        this->y = y;
    };
};
vector<float> get_triangle_vertices(float scale = 1.0f, Coordinate offset = {0.0f, 0.0f})
{
    vector<float> vertices = {
        -0.5f + offset.x,
        -0.5f + offset.y,
        0.0f,
        0.5f + offset.x,
        -0.5f + offset.y,
        0.0f,
        0.0f + offset.x,
        0.5f + offset.y,
        0.0f,

    };
    return vertices;
};
vector<int> get_triangle_indices()
{
    return {
        0, 1, 2};
}
vector<float> get_square_vertices()
{
    return {
        -.5f,
        -.9f,
        .0f,
        +.5f,
        -.9f,
        .0f,
        +.5f,
        +.9f,
        .0f,
        -.5f,
        +.9f,
        .0f,
    };
}
vector<int> get_square_indices()
{
    return {
        0, 1, 2,
        2, 3, 0};
};
using namespace glm;

std::tuple<vector<VertexData>, vector<int>> get_quad_vertices_indices(const glm::vec3 &center, 
const glm::vec3 &direction, const float spread, const int index_offset)
{
    glm::vec3 A{direction.y, direction.z,direction.x};
    glm::vec3 B{glm::cross(A, direction)};
    // Order: Top left, top right, bottom left, bottom right
    glm::vec3 tl = center+(A*spread)-(B*spread);
    glm::vec3 col_tl{0.0};
    glm::vec2 uv_tl{0.0,1.0};
    auto tl_vertex_data = VertexData(tl,col_tl, uv_tl);

    glm::vec3 tr = center+(A*spread)+(B*spread);
    glm::vec3 col_tr{1.0,0.0,0.0};
    glm::vec2 uv_tr{1.0,1.0};
    auto tr_vertex_data = VertexData(tr,col_tr, uv_tr);

    
    glm::vec3 bl = center-(A*spread)-(B*spread);
    glm::vec3 col_bl{0.0,1.0,0.0};
    glm::vec2 uv_bl{0.0,0.0};
    auto bl_vertex_data = VertexData(bl,col_bl, uv_bl);

    
    glm::vec3 br = center-(A*spread)+(B*spread);
    glm::vec3 col_br{0.0,0.0,1.0};
    glm::vec2 uv_br{1.0,0.0};
    auto br_vertex_data = VertexData(br,col_br, uv_br);

    
    vector<VertexData> vertices{tl_vertex_data,tr_vertex_data,bl_vertex_data,br_vertex_data};
    vector<int> indices{
        0,1,2,
        1,3,2
    };
    for (int i =0; i<indices.size();i++){
        indices[i]= index_offset+indices[i];
    }
    return {vertices, indices};
}