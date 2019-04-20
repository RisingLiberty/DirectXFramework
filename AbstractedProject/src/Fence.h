#pragma once

class Fence
{
public:
	Fence(UINT initialValue, D3D12_FENCE_FLAGS flags, ID3D12Device* pDevice);
	~Fence();

private:
	ComPtr<ID3D12Fence> m_Fence;
};