/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <unordered_map>
#include <unordered_set>
#include "CreateGlResource.h"

class OpenGLResourceFactory
{
public:
	~OpenGLResourceFactory();

	GLuint CreateVertexBuffer();
	GLuint CreateIndexBuffer();
	GLuint CreateVertexArray();
	GLuint CreateTexture(const char* imagePath);
	GLuint CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	GLuint CreateFrameBuffer();
	GLuint CreateBuffer();
	GLuint CreateRenderBuffer(int width, int height);
	void SetUniformMat4(GLuint program, const char* name, const glm::mat4& matrix);
	void BindVertexArray(GLuint vao);
	void BindVertexBuffer(GLuint vbo, GLuint vao, GLuint attributeIndex, int size, int stride, int offset);
	void BindIndexBuffer(GLuint ibo);
	void UseProgram(GLuint program);
	void ClearScreen(float r, float g, float b, float a);
	void SetViewport(int x, int y, int width, int height);
	void BindTexture(GLenum target, GLuint texture);
	void BindFrameBuffer(GLenum target, GLuint framebuffer);

private:
	GLuint CompileShader(GLenum shaderType, const char* source);
	std::list<CreatedGlResource> createdResources = std::list<CreatedGlResource>();
};