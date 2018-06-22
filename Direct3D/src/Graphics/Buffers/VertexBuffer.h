#pragma once

#include <d3d11.h>
#include "BufferLayout.h"
#include "../Context.h"
#include "../Shader.h"

struct VertexData
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

	unsigned int m_Size;

public:
	VertexBuffer(const Context& context);
	~VertexBuffer();

	void Resize(unsigned int size);

	void SetData(VertexData data[], unsigned int size);
	void SetLayout(const BufferLayout&, const Shader& shader);

	void Bind() const;
	void Unbind() const;
};