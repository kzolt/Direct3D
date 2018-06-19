#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const Context& context, const Shader& shader)
	: m_Context(context), m_Shader(shader), m_Size(0)
{
	memset(&m_BufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
}

VertexBuffer::~VertexBuffer()
{
	m_BufferHandle->Release();
	m_InputLayout->Release();
}

void VertexBuffer::Resize(unsigned int size)
{
	m_Size = size;
	m_BufferDesc.ByteWidth = size;
	m_Context.dev->CreateBuffer(&m_BufferDesc, NULL, &m_BufferHandle);
}

void VertexBuffer::SetData(VERTEX data[], unsigned int size)
{
	if (m_Size < size)
		Resize(size);

	m_Context.devcon->Map(m_BufferHandle, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MappedSubresource);
	memcpy(m_MappedSubresource.pData, data, size);
	m_Context.devcon->Unmap(m_BufferHandle, NULL);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_Context.dev->CreateInputLayout(ied, 2, m_Shader.GetVSBlob()->GetBufferPointer(), m_Shader.GetVSBlob()->GetBufferSize(), &m_InputLayout);
}

void VertexBuffer::Bind() const
{
	// Bind Vertex Buffers
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	m_Context.devcon->IASetInputLayout(m_InputLayout);
	m_Context.devcon->IASetVertexBuffers(0, 1, &m_BufferHandle, &stride, &offset);
	m_Context.devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void VertexBuffer::Unbind() const
{

}