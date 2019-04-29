#pragma once

class Device;

class Fence
{
public:
	Fence(Device* pDevice, UINT initialValue, D3D12_FENCE_FLAGS flags);
	~Fence();

	unsigned __int64 GetValue() const;
	void SetEventOnCompletion(unsigned int currentValue, HANDLE eventHandle);

	ID3D12Fence* GetFence() const;
	ID3D12Fence* const* GetFenceAddress() const;

private:
	ComPtr<ID3D12Fence> m_Fence;
};