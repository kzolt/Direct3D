#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int count, const Context& context)
	: m_Count(count), m_Context(context)
{
	D3D11_BUFFER_DESC ibd;
	memset(&ibd, 0, sizeof(D3D11_BUFFER_DESC));

	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(unsigned int) * count;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;

	context.dev->CreateBuffer(&ibd, NULL, &m_BufferHandle);
}

IndexBuffer::~IndexBuffer()
{
	m_BufferHandle->Release();
}

void IndexBuffer::SetData(const unsigned int* data)
{
	m_Context.devcon->Map(m_BufferHandle, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MappedSubresource);
	memcpy(m_MappedSubresource.pData, data, sizeof(unsigned int) * m_Count);
	m_Context.devcon->Unmap(m_BufferHandle, 0);
}

void IndexBuffer::Bind() const
{
	m_Context.devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Context.devcon->IASetIndexBuffer(m_BufferHandle, DXGI_FORMAT_R32_UINT, 0);
}

void IndexBuffer::Unbind() const
{

}