#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(const Context& context, unsigned int size)
	: m_Context(context)
{
	memset(&m_BufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.ByteWidth = size;
	m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	context.dev->CreateBuffer(&m_BufferDesc, NULL, &m_BufferHandle);
}

ConstantBuffer::~ConstantBuffer()
{
	m_BufferHandle->Release();
}

void ConstantBuffer::UpdateBuffer(const CBuffer& perFrame)
{
	m_Context.devcon->UpdateSubresource(m_BufferHandle, 0, 0, &perFrame, 0, 0);
}

void ConstantBuffer::UpdateBuffer(const DirectX::XMMATRIX& matrix)
{
	m_Context.devcon->UpdateSubresource(m_BufferHandle, 0, 0, &matrix, 0, 0);
}

void ConstantBuffer::Bind() const
{
	m_Context.devcon->VSSetConstantBuffers(0, 1, &m_BufferHandle);
}

void ConstantBuffer::Unbind() const
{

}