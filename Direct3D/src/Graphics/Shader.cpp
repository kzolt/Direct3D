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
	HRESULT hr = D3DCompileFromFile(L"res/shaders/shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &m_Vs, &m_VSErr);
	if (FAILED(hr))
	{
		std::ofstream stream("res/errors/shader_vs_error.error", std::ofstream::out);
		stream.write((char*)m_VSErr->GetBufferPointer(), m_VSErr->GetBufferSize());
		m_VSErr->Release();
		stream.close();
	}

	hr = D3DCompileFromFile(L"res/shaders/shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &m_Ps, &m_PSErr);
	if (FAILED(hr))
	{
		std::ofstream stream("res/errors/shader_ps_error.error");
		stream.write((char*)m_PSErr->GetBufferPointer(), m_PSErr->GetBufferSize());
		m_VSErr->Release();
		stream.close();
	}
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