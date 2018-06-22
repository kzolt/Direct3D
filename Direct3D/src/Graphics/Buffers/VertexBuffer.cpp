#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const Context& context)
	: m_Context(context), m_Size(0)
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

void VertexBuffer::SetData(VertexData data[], unsigned int size)
{
	if (m_Size < size)
		Resize(size);

	m_Context.devcon->Map(m_BufferHandle, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_MappedSubresource);
	memcpy(m_MappedSubresource.pData, data, size);
	m_Context.devcon->Unmap(m_BufferHandle, NULL);
}

void VertexBuffer::SetLayout(const BufferLayout& layout, const Shader& shader)
{
	const auto& elements = layout.GetLayout();
	D3D11_INPUT_ELEMENT_DESC* desc = new D3D11_INPUT_ELEMENT_DESC[elements.size()];
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		desc[i] = { element.name.c_str(), 0, (DXGI_FORMAT)element.type, 0, element.offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	m_Context.dev->CreateInputLayout(desc, elements.size(), shader.GetVSBlob()->GetBufferPointer(), shader.GetVSBlob()->GetBufferSize(), &m_InputLayout);
	delete desc;
}

void VertexBuffer::Bind() const
{
	// Bind Vertex Buffers
	UINT stride = sizeof(VertexData);
	UINT offset = 0;
	m_Context.devcon->IASetInputLayout(m_InputLayout);
	m_Context.devcon->IASetVertexBuffers(0, 1, &m_BufferHandle, &stride, &offset);
	m_Context.devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void VertexBuffer::Unbind() const
{

}