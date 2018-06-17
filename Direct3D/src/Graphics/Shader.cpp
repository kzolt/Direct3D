#include "Shader.h"

Shader::Shader(const std::wstring& filepath, const Context& context)
{
	CompileShaders(filepath);
	InitPipeline(context);
}

Shader::~Shader()
{
	m_VertexShaderHandle->Release();
	m_PixelShaderHandle->Release();
	m_Vs->Release();
	m_Ps->Release();
}

void Shader::CompileShaders(const std::wstring& filepath)
{
	// Compile the shaders
	D3DCompileFromFile(filepath.data(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &m_Vs);
	D3DCompileFromFile(filepath.data(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &m_Ps);
}

void Shader::InitPipeline(const Context& context)
{
	// encapsulate shaders into shader objects
	context.dev->CreateVertexShader(m_Vs->GetBufferPointer(), m_Vs->GetBufferSize(), NULL, &m_VertexShaderHandle);
	context.dev->CreatePixelShader(m_Ps->GetBufferPointer(), m_Ps->GetBufferSize(), NULL, &m_PixelShaderHandle);

	// Set the shader objects
	context.devcon->VSSetShader(m_VertexShaderHandle, 0, 0);
	context.devcon->PSSetShader(m_PixelShaderHandle, 0, 0);
}