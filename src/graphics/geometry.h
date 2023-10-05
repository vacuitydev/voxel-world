#pragma once
#include "graphics/transform.h"
#include "graphics/shader.h"
#include "model.h"
#include <glm/gtc/type_ptr.hpp>
class Geometry{
public:
    
    Model* model;
    Shader* shader;
    Transform transform = Transform();

    Geometry(){};
    Geometry(Model* m= nullptr, Shader* s=nullptr, Transform t= Transform()):model(m), shader(s), transform(t){
        
    }
    void Translate(glm::vec3){
        // transform
    }
    void Draw(){
        shader->use();
    	unsigned int transformLoc = glGetUniformLocation(shader->Id, "transform");
    	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform.Matrix()));  
        model->Draw();
    }
};