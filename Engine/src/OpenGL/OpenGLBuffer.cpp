#include "ENPH.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace Engine 
{
	/////////////////////////////////////////////////////////////////////////////////////////////
	//VERTEX BUFFER//////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size, float* vertecies)
	{
		glCreateBuffers(1, &mRenderID);
		glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
		glBufferData(GL_ARRAY_BUFFER, size, vertecies, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &mRenderID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	//INDEX BUFFER///////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int count, unsigned int* indices)
		:mCount(count)
	{
		glCreateBuffers(1, &mRenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &mRenderID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}