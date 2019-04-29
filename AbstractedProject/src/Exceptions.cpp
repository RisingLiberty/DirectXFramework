#include "stdafx.h"
#include "Exceptions.h"

#include <comdef.h>

Exception::Exception() :
	m_ErrorCode(S_OK),
	m_FunctionName(L""),
	m_FileName(L""),
	m_LineNr(-1)
{
}

Exception::Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& fileName, int lineNumber):
	m_ErrorCode(hr),
	m_FunctionName(functionName),
	m_FileName(fileName),
	m_LineNr(lineNumber)
{

}

std::wstring Exception::ToString() const
{
	// Get the string description of the error code
	_com_error err(m_ErrorCode);
	std::wstring msg = err.ErrorMessage();

	std::wstringstream ss;

	ss << m_FunctionName << L" failed in " << m_FileName << L" on line " << m_LineNr << L"\n";
	ss << L"error: " << msg << L"\n";

	return ss.str();
}


#define CreateException(className, message)\
className::className() :\
Exception()\
{\
\
}\
\
className::className(HRESULT hr, const std::wstring& functionName, const std::wstring& fileName, int lineNumber) :\
	Exception(hr, functionName, fileName, lineNumber)\
{\
\
}\
\
std::wstring className::ToString() const\
{\
	std::wstringstream ss;\
\
	ss << "---" << message << "---\n" << Exception::ToString();\
\
	return ss.str();\
}\


CreateException(DefaultException, "Default exception");
CreateException(WindowException, "Window exception");
CreateException(DeviceException, "Device exception");
CreateException(CommandQueueException, "Command Queue exception");
CreateException(SwapChainException, "Swapchain exception");
CreateException(CommandListException, "Command List Exception");
CreateException(UploadBufferException, "Upload Buffer Exception");