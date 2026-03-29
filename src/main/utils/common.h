#pragma once
#ifdef _WIN32
#define PLATFORM_FOLDER "win64"
#else
#define PLATFORM_FOLDER "linuxsteamrt64"
#endif

void ExitError(const char* pMsg, ...);

class SimpleCUtlString
{
public:
	const char* Get();

private:
	const char* m_pString = nullptr;
};
