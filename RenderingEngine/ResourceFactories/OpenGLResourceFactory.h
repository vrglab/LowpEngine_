#pragma once

struct CreatedGlResource
{
public:
	GLuint glHandle;
	int Type = 0;
};

enum ResourceType
{
	ShaderProgram = 0,
	Texture = 1,
	Buffer = 2,
	Shader = 3,
	FrameBuffer = 4,
	RenderBuffer = 5,
	VertexArray = 6,
	VertexBuffer = 7,
	IndexBuffer = 8
};


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

