#pragma once
#include <iostream>
#include "../utils/read_string_from_file.h"
using namespace std;
const int SHADER_DEBUG=1;
void check_shader_error(unsigned int Id)
{
    int success;
    char infoLog[512];
    glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
}
void check_program_error(unsigned int Id)
{
    int success;
    char infoLog[512];
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(Id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::Program::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
}
class Shader
{
public:
    unsigned int Id;
    unsigned int VertexShaderId;
    unsigned int FragmentShaderId;
    const char* defaultVertexShaderPath =   "./shaders/default.vert";
    const char* defaultFragmentShaderPath = "./shaders/default.vert";
    
    // Build with the default shaders
    Shader(){
        if(SHADER_DEBUG){
            cout<<"Setting up null shader\n";
        }
        auto result = read_string_from_file(defaultVertexShaderPath);
        if (holds_alternative<Exception>(result))
        {
            cerr << get<Exception>(result).message << endl;
            throw("Cannot read from vertex shader file");
        }
        string shader_string = get<std::string>(result);
        char *vertex_shader_source = new char[shader_string.length()+1];
        cout<< "Vertex shader"<<vertex_shader_source<<endl;
        strcpy_s(vertex_shader_source,shader_string.length()+1, shader_string.c_str());
        result = read_string_from_file(defaultFragmentShaderPath);
        if (holds_alternative<Exception>(result))
        {
            cerr << get<Exception>(result).message << endl;
            throw("Cannot read from fragment shader file");
        }
        shader_string = get<std::string>(result);
        const char *fragment_shader_source =shader_string.c_str();
        InitializeShader(vertex_shader_source, fragment_shader_source);
    }
    Shader(const char *vertexShaderSource, const char *fragmentShaderSource)
    {
        if(SHADER_DEBUG){
            cout<<"Setting up shader\n";
        }
        InitializeShader(vertexShaderSource, fragmentShaderSource);
    }
    void InitializeShader(const char *vertexShaderSource, const char *fragmentShaderSource){
                // Create the vertex shader
        VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(VertexShaderId, 1, &vertexShaderSource, NULL);
        glCompileShader(VertexShaderId);
        check_shader_error(VertexShaderId);
        // Create fragment shader
        FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FragmentShaderId, 1, &fragmentShaderSource, NULL);
        glCompileShader(FragmentShaderId);
        check_shader_error(FragmentShaderId);

        // Create a shader program
        Id = glCreateProgram();
        // Link them
        glAttachShader(Id, VertexShaderId);
        glAttachShader(Id, FragmentShaderId);
        glLinkProgram(Id);
        check_program_error(Id);
        glDeleteShader(VertexShaderId);
        glDeleteShader(FragmentShaderId);
    }
    static Shader shaderFromFiles(const char *vertexShaderPath, const char *fragmentShaderPath)
    {
        if(SHADER_DEBUG){
            cout<<"Reading shaders from "<<vertexShaderPath<< " " << fragmentShaderPath<< endl;
        }
        auto result = read_string_from_file(vertexShaderPath);
        if (holds_alternative<Exception>(result))
        {
            cerr << get<Exception>(result).message << endl;
            throw("Cannot read from vertex shader file");
        }

        string shader_string = get<std::string>(result);
        
        char *vertex_shader_source = new char[shader_string.length()+1];
        strcpy(vertex_shader_source, shader_string.c_str());
        if(SHADER_DEBUG){
            cout<<"Vertex shader source" << vertex_shader_source<<endl;
        }
        result = read_string_from_file(fragmentShaderPath);
        if (holds_alternative<Exception>(result))
        {
            cerr << get<Exception>(result).message << endl;
            throw("Cannot read from fragment shader file");
        }
        shader_string = get<std::string>(result);
        const char *fragment_shader_source =shader_string.c_str();
        if(SHADER_DEBUG){
            cout<<"Fragment shader source" << vertex_shader_source<<endl;
        }
        return Shader(vertex_shader_source, fragment_shader_source);
    }
    void use(){
        glUseProgram(Id);
    }
};