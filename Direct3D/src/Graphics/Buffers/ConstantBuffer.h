#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "../Context.h"

struct CBufferPerFrame
{
	float r, g, b, a;
	float x, y, z;
};

class ConstantBuffer
{
private:
	ID3D11Buffer* m_BufferHandle;
	D3D11_BUFFER_DESC m_BufferDesc;

	const Context& m_Context;

public:
	ConstantBuffer(const Context& context, unsigned int size);
	~ConstantBuffer();

	void Bind() const;
	void Unbind() const;

	void UpdateBuffer(const CBufferPerFrame& colorMod);
	void UpdateBuffer(const DirectX::XMMATRIX& matrix);

};