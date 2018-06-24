#pragma once

#include <d3d11.h>

#include "../Context.h"

class IndexBuffer
{
private:
	ID3D11Buffer* m_BufferHandle;
	D3D11_MAPPED_SUBRESOURCE m_MappedSubresource;

	const Context& m_Context;

	unsigned int m_Count;

public:
	IndexBuffer(unsigned int count, const Context& context);
	~IndexBuffer();

	void SetData(const unsigned int* data);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};