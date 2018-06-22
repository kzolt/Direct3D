#pragma once

#include <d3d11.h>
#include <string>
#include <vector>

struct BufferElement
{
	std::string name;
	unsigned int type;
	unsigned int size;
	unsigned int count;
	unsigned int offset;
	bool normalized;
};

class BufferLayout
{
private:
	std::vector<BufferElement> m_Layout;
	unsigned int m_Size;

public:
	BufferLayout()
		: m_Size(0) {}

	template<typename T>
	void Push(const std::string& name, unsigned int count = 1, bool normalized = false)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(const std::string& name, unsigned int count, bool normalized)
	{
		m_Layout.push_back({ name, DXGI_FORMAT_R32G32B32_FLOAT, sizeof(float), count, m_Size, normalized });
		m_Size += count * sizeof(float);
	}

	inline const std::vector<BufferElement>& GetLayout() const { return m_Layout; }
	inline unsigned int GetStride() const { return m_Size; }
};