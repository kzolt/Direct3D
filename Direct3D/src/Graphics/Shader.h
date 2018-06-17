#pragma once

#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "Context.h"

class Shader
{
private:
	ID3D11VertexShader* m_VertexShaderHandle;
	ID3D11PixelShader* m_PixelShaderHandle;
	ID3DBlob *m_Vs, *m_Ps;

public:
	Shader(const std::wstring& filepath, const Context& context);
	~Shader();

private:
	void CompileShaders(const std::wstring& filepath);
	void InitPipeline(const Context& context);
};