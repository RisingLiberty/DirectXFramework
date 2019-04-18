#pragma once

class Exception
{
public:
	Exception();
	Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& fileName, int lineNumber);

	virtual std::wstring ToString() const;

private:
	HRESULT m_ErrorCode;
	std::wstring m_FunctionName;
	std::wstring m_FileName;
	int m_LineNr;
};

#define DeclareException(className)\
class className : public Exception\
{\
public:\
	className();\
	className(HRESULT hr, const std::wstring& functionName, const std::wstring& fileName, int lineNumber);\
\
	virtual std::wstring ToString() const override;\
};\

DeclareException(DefaultException);
DeclareException(WindowException);