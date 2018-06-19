#pragma once

#include <d3d11.h>
#include "../Context.h"
#include "../Shader.h"

struct VERTEX
{
	float x, y, z;
	float r, g, b, a;
};

class VertexBuffer
{
private:
	D3D11_MAPPED_SUBRESOURCE m_MappedSubresource;
	D3D11_BUFFER_DESC m_BufferDesc;
	ID3D11Buffer* m_BufferHandle;
	ID3D11InputLayout* m_InputLayout;

	const Context& m_Context;
	const Shader& m_Shader;

	unsigned int m_Size;

public:
	VertexBuffer(const Context& context, const Shader& shader);
	~VertexBuffer();

	void Resize(unsigned int size);

	void SetData(VERTEX data[], unsigned int size);

	void Bind() const;
	void Unbind() const;
};