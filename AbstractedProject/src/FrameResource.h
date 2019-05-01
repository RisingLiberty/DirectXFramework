#pragma once

class CommandAllocator;
struct PassConstants;
struct ObjectConstants;
struct MaterialConstants;

class Device;

#include "UploadBuffer.h"

class FrameResource
{
public:
	FrameResource(Device* pDevice, unsigned int passCount, unsigned int objectCount, unsigned int materialCount);

private:
	std::unique_ptr<CommandAllocator> m_pCommandAllocator;
	std::unique_ptr<UploadBuffer<PassConstants>> m_pPassConstants;
	std::unique_ptr<UploadBuffer<ObjectConstants>> m_pObjectConstants;
	std::unique_ptr<UploadBuffer<MaterialConstants>> m_pMaterialConstants;
};