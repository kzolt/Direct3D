#include "Shader.h"

Shader::Shader(const Context& context)
{
	CompileShaders();
	InitPipeline(context);
}

Shader::~Shader()
{
	m_VertexShaderHandle->Release();
	m_PixelShaderHandle->Release();
	m_Vs->Release();
	m_Ps->Release();
}

void Shader::CompileShaders()
{
	// Compile the shaders
	D3DCompileFromFile(L"res/shaders/shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &m_Vs, 0);
	D3DCompileFromFile(L"res/shaders/shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &m_Ps, 0);
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