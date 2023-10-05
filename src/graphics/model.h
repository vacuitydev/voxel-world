#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include "utils/vertex_data.h"
const int MODEL_DEBUG =1;
class Model
{
public:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    vector<VertexData> vertices{};
    vector<int> indices{};
    Model(){
        if(MODEL_DEBUG){
            std::cout<<"Setting up null model\n";
        }
        setupOpenGLBuffers(vertices, indices);
    }
    Model(vector<VertexData> _vertices, vector<int> _indices) : vertices(_vertices), indices(_indices)
    {
        setupOpenGLBuffers(vertices, indices);
    
    };
    Model(vector<glm::vec3> _vertices, vector<int> _indices) : indices(_indices)
    {
        // vertices.resize(_vertices.size());
        for (const glm::vec3 &vertex : _vertices)
        {
            vertices.push_back(VertexData(vertex));
        }
        setupOpenGLBuffers(vertices, indices);  
    };
    void Draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
private:
void setupOpenGLBuffers(const vector<VertexData>& vertices, const vector<int>& indices) {
    if(MODEL_DEBUG){
        std::cout<<"Setting up model with "<<vertices.size()<<" vertices\n";
        for(VertexData v: vertices){
            std::cout<<"Vertex "<< v.to_string()<<endl;
        }
    }
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);

    GLsizei stride = ((8) * sizeof(float));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}
};