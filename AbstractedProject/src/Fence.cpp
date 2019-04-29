#include "stdafx.h"
#include "Fence.h"

#include "Device.h"

Fence::Fence(Device* pDevice, UINT initialValue, D3D12_FENCE_FLAGS flags)
{
	pDevice->CreateFence(initialValue, flags, m_Fence.ReleaseAndGetAddressOf());
}

Fence::~Fence()
{

}

unsigned __int64 Fence::GetValue() const
{
	return m_Fence->GetCompletedValue();
}

void Fence::SetEventOnCompletion(unsigned int currentValue, HANDLE eventHandle)
{
	m_Fence->SetEventOnCompletion(currentValue, eventHandle);
}

ID3D12Fence* Fence::GetFence() const
{
	return m_Fence.Get();
}

ID3D12Fence* const* Fence::GetFenceAddress() const
{
	return m_Fence.GetAddressOf();
}