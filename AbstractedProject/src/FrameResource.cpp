#include "stdafx.h"
#include "FrameResource.h"

#include "Device.h"
#include "CommandAllocator.h"
#include "ConstantBuffers.h"

FrameResource::FrameResource(Device* pDevice, unsigned int passCount, unsigned int objectCount, unsigned int materialCount)
{
	m_pCommandAllocator = std::make_unique<CommandAllocator>(pDevice);

	m_pPassConstants = std::make_unique<UploadBuffer<PassConstants>>(pDevice, passCount, true);
	m_pObjectConstants = std::make_unique<UploadBuffer<ObjectConstants>>(pDevice, objectCount, true);
	m_pMaterialConstants = std::make_unique<UploadBuffer<MaterialConstants>>(pDevice, materialCount, true);
}

CommandAllocator* FrameResource::GetCommandAllocator() const
{
	return m_pCommandAllocator.get();
}

UploadBuffer<PassConstants>* FrameResource::GetPassConstants() const
{
	return m_pPassConstants.get();
}

UploadBuffer<ObjectConstants>* FrameResource::GetObjectConstants() const
{
	return m_pObjectConstants.get();
}

UploadBuffer<MaterialConstants>* FrameResource::GetMaterialConstants() const
{
	return m_pMaterialConstants.get();
}
