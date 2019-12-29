#pragma once
#ifndef _FE_DEFINE
#define _FE_DEFINE

#include <vector>
#include <unordered_map>

#include <memory>

#include <tchar.h>
#include <string>

namespace FE
{
	using TCHAR		= TCHAR;
	using LPTSTR	= TCHAR*;
	using LPCTSTR	= const TCHAR*;

	using INT8		= char;
	using INT16		= short;
	using INT32		= int;
	using INT64		= long long;

	using UINT8		= unsigned char;
	using UINT16	= unsigned short;
	using UINT32	= unsigned int;
	using UINT64	= unsigned long long;

	using FLOAT		= float;
	using DOUBLE	= double;

#ifdef _UNICODE
	using tstring	= std::wstring;
#else
	using tstring	= std::string;
#endif
	template<typename T>
	inline void SAFE_DELETE(T* ptr)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
	template<typename T>
	inline void SAFE_DELARR(T* ptr)
	{
		if (ptr != nullptr)
		{
			delete[] ptr;
			ptr = nullptr;
		}
	}
}

#endif