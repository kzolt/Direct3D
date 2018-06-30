#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "../Context.h"

struct CBuffer
{
	DirectX::XMMATRIX matrix;
	DirectX::XMMATRIX rotation;
	DirectX::XMVECTOR lightvec;
	DirectX::XMVECTOR lightcol;
	DirectX::XMVECTOR ambientcol;
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

	void UpdateBuffer(const CBuffer& colorMod);
	void UpdateBuffer(const DirectX::XMMATRIX& matrix);

};