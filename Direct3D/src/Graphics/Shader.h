#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <fstream>

#include "Context.h"

class Shader
{
private:
	ID3D11VertexShader* m_VertexShaderHandle;
	ID3D11PixelShader* m_PixelShaderHandle;
	ID3DBlob *m_Vs, *m_Ps;
	ID3DBlob *m_VSErr, *m_PSErr;

public:
	Shader(const Context& context);
	~Shader();

	inline ID3D11VertexShader* GetVSHandle() const { return m_VertexShaderHandle; }
	inline ID3D11PixelShader* GetPSHandle() const { return m_PixelShaderHandle; }
	inline ID3DBlob* GetVSBlob() const { return m_Vs; }
	inline ID3DBlob* GetPSBlob() const { return m_Ps; }

private:
	void CompileShaders();
	void InitPipeline(const Context& context);
};