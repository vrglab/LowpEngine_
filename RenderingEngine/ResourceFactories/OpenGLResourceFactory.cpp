#include "lprdpch.h"
#include "OpenGLResourceFactory.h"

OpenGLResourceFactory::~OpenGLResourceFactory()
{
	for each (CreatedGlResource resource in createdResources)
	{
		switch (resource.Type)
		{
			case ResourceType::Buffer:
				glDeleteBuffers(1, &resource.glHandle);
				break;
			case ResourceType::ShaderProgram:
				glDeleteProgram(resource.glHandle);
				break;
			case ResourceType::Texture:
				glDeleteTextures(1, &resource.glHandle);
				break;
			case ResourceType::Shader:
				glDeleteShader(resource.glHandle);
				break;
			case ResourceType::FrameBuffer:
				glDeleteFramebuffers(1, &resource.glHandle);
				break;
			case ResourceType::RenderBuffer:
				glDeleteRenderbuffers(1, &resource.glHandle);
				break;
		}
	}
}

GLuint OpenGLResourceFactory::CreateVertexBuffer()
{
	return GLuint();
}

GLuint OpenGLResourceFactory::CreateIndexBuffer()
{
	return GLuint();
}

GLuint OpenGLResourceFactory::CreateVertexArray()
{
	GLuint buffer;
	glCreateVertexArrays(1, &buffer);
	CreatedGlResource resource = {};
	resource.glHandle = buffer;
	resource.Type = ResourceType::VertexArray;
	createdResources.push_back(resource);
	return buffer;
}

GLuint OpenGLResourceFactory::CreateTexture(const char* imagePath)
{
	return GLuint();
}

GLuint OpenGLResourceFactory::CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	return GLuint();
}

GLuint OpenGLResourceFactory::CreateFrameBuffer()
{
	return GLuint();
}

GLuint OpenGLResourceFactory::CreateBuffer()
{
	GLuint buffer;
	glCreateBuffers(1, &buffer);
	CreatedGlResource resource = {};
	resource.glHandle = buffer;
	resource.Type = ResourceType::Buffer;
	createdResources.push_back(resource);
	return buffer;
}

GLuint OpenGLResourceFactory::CreateRenderBuffer(int width, int height)
{
	return GLuint();
}

void OpenGLResourceFactory::SetUniformMat4(GLuint program, const char* name, const glm::mat4& matrix)
{
}

void OpenGLResourceFactory::BindVertexArray(GLuint vao)
{
}

void OpenGLResourceFactory::BindVertexBuffer(GLuint vbo, GLuint vao, GLuint attributeIndex, int size, int stride, int offset)
{
}

void OpenGLResourceFactory::BindIndexBuffer(GLuint ibo)
{
}

void OpenGLResourceFactory::UseProgram(GLuint program)
{
}

void OpenGLResourceFactory::ClearScreen(float r, float g, float b, float a)
{
}

void OpenGLResourceFactory::SetViewport(int x, int y, int width, int height)
{
}

void OpenGLResourceFactory::BindTexture(GLenum target, GLuint texture)
{
}

void OpenGLResourceFactory::BindFrameBuffer(GLenum target, GLuint framebuffer)
{
}

GLuint OpenGLResourceFactory::CompileShader(GLenum shaderType, const char* source)
{
	return GLuint();
}
