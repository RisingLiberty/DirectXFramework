#include "stdafx.h"
#include "Fence.h"

#include "Utils.h"

Fence::Fence(UINT initialValue, D3D12_FENCE_FLAGS flags, ID3D12Device* pDevice)
{
	ThrowIfFailed(pDevice->CreateFence(initialValue, flags, IID_PPV_ARGS(m_Fence.ReleaseAndGetAddressOf())));

}

Fence::~Fence()
{

}
