#pragma once
#include "pch.h"
#include <map>
#include "Camera.h"
#include "Constants.h"
#include "ppltasks_extra.h"
#include "Common\DirectXHelper.h"
#include "DDSTextureLoader.h"


namespace ToolkitHelper{

	///////////////////////////////////////////////////////////////////////////////////////////
	//
	// Simple COM helper template functions for safe AddRef() and Release() of IUnknown objects.
	//
	template <class T> inline LONG SafeAddRef(T* pUnk) { ULONG lr = 0; if (pUnk != nullptr) { lr = pUnk->AddRef(); } return lr; }
	template <class T> inline LONG SafeRelease(T*& pUnk) { ULONG lr = 0; if (pUnk != nullptr) { lr = pUnk->Release(); pUnk = nullptr; } return lr; }
	//
	//
	///////////////////////////////////////////////////////////////////////////////////////////



	const BYTE VSD3DStarter_VS [] =
	{
		68, 88, 66, 67, 6, 246,
		181, 252, 252, 142, 75, 224,
		64, 3, 123, 57, 145, 98,
		23, 7, 1, 0, 0, 0,
		52, 10, 0, 0, 6, 0,
		0, 0, 56, 0, 0, 0,
		56, 2, 0, 0, 60, 5,
		0, 0, 184, 5, 0, 0,
		152, 8, 0, 0, 72, 9,
		0, 0, 65, 111, 110, 57,
		248, 1, 0, 0, 248, 1,
		0, 0, 0, 2, 254, 255,
		148, 1, 0, 0, 100, 0,
		0, 0, 5, 0, 36, 0,
		0, 0, 96, 0, 0, 0,
		96, 0, 0, 0, 36, 0,
		1, 0, 96, 0, 0, 0,
		1, 0, 1, 0, 1, 0,
		0, 0, 0, 0, 2, 0,
		0, 0, 3, 0, 2, 0,
		0, 0, 0, 0, 2, 0,
		4, 0, 4, 0, 5, 0,
		0, 0, 0, 0, 2, 0,
		16, 0, 2, 0, 9, 0,
		0, 0, 0, 0, 2, 0,
		20, 0, 1, 0, 11, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 2, 254, 255,
		81, 0, 0, 5, 12, 0,
		15, 160, 0, 0, 128, 63,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		31, 0, 0, 2, 5, 0,
		0, 128, 0, 0, 15, 144,
		31, 0, 0, 2, 5, 0,
		1, 128, 1, 0, 15, 144,
		31, 0, 0, 2, 5, 0,
		2, 128, 2, 0, 15, 144,
		31, 0, 0, 2, 5, 0,
		3, 128, 3, 0, 15, 144,
		31, 0, 0, 2, 5, 0,
		4, 128, 4, 0, 15, 144,
		9, 0, 0, 3, 0, 0,
		4, 192, 0, 0, 228, 144,
		7, 0, 228, 160, 5, 0,
		0, 3, 0, 0, 15, 224,
		3, 0, 228, 144, 1, 0,
		228, 160, 4, 0, 0, 4,
		0, 0, 7, 128, 4, 0,
		196, 144, 12, 0, 208, 160,
		12, 0, 197, 160, 8, 0,
		0, 3, 1, 0, 1, 224,
		0, 0, 228, 128, 9, 0,
		244, 160, 8, 0, 0, 3,
		1, 0, 2, 224, 0, 0,
		228, 128, 10, 0, 244, 160,
		8, 0, 0, 3, 2, 0,
		1, 224, 1, 0, 228, 144,
		2, 0, 228, 160, 8, 0,
		0, 3, 2, 0, 2, 224,
		1, 0, 228, 144, 3, 0,
		228, 160, 8, 0, 0, 3,
		2, 0, 4, 224, 1, 0,
		228, 144, 4, 0, 228, 160,
		9, 0, 0, 3, 0, 0,
		1, 128, 0, 0, 228, 144,
		2, 0, 228, 160, 9, 0,
		0, 3, 0, 0, 2, 128,
		0, 0, 228, 144, 3, 0,
		228, 160, 9, 0, 0, 3,
		0, 0, 4, 128, 0, 0,
		228, 144, 4, 0, 228, 160,
		2, 0, 0, 3, 4, 0,
		7, 224, 0, 0, 228, 129,
		11, 0, 228, 160, 1, 0,
		0, 2, 3, 0, 7, 224,
		0, 0, 228, 128, 9, 0,
		0, 3, 0, 0, 1, 128,
		0, 0, 228, 144, 5, 0,
		228, 160, 9, 0, 0, 3,
		0, 0, 2, 128, 0, 0,
		228, 144, 6, 0, 228, 160,
		9, 0, 0, 3, 0, 0,
		4, 128, 0, 0, 228, 144,
		8, 0, 228, 160, 4, 0,
		0, 4, 0, 0, 3, 192,
		0, 0, 170, 128, 0, 0,
		228, 160, 0, 0, 228, 128,
		1, 0, 0, 2, 0, 0,
		8, 192, 0, 0, 170, 128,
		1, 0, 0, 2, 5, 0,
		15, 224, 2, 0, 228, 144,
		1, 0, 0, 2, 6, 0,
		7, 224, 1, 0, 228, 144,
		255, 255, 0, 0, 83, 72,
		68, 82, 252, 2, 0, 0,
		64, 0, 1, 0, 191, 0,
		0, 0, 89, 0, 0, 4,
		70, 142, 32, 0, 0, 0,
		0, 0, 2, 0, 0, 0,
		89, 0, 0, 4, 70, 142,
		32, 0, 2, 0, 0, 0,
		21, 0, 0, 0, 95, 0,
		0, 3, 242, 16, 16, 0,
		0, 0, 0, 0, 95, 0,
		0, 3, 114, 16, 16, 0,
		1, 0, 0, 0, 95, 0,
		0, 3, 242, 16, 16, 0,
		2, 0, 0, 0, 95, 0,
		0, 3, 242, 16, 16, 0,
		3, 0, 0, 0, 95, 0,
		0, 3, 50, 16, 16, 0,
		4, 0, 0, 0, 103, 0,
		0, 4, 242, 32, 16, 0,
		0, 0, 0, 0, 1, 0,
		0, 0, 101, 0, 0, 3,
		242, 32, 16, 0, 1, 0,
		0, 0, 101, 0, 0, 3,
		50, 32, 16, 0, 2, 0,
		0, 0, 101, 0, 0, 3,
		114, 32, 16, 0, 3, 0,
		0, 0, 101, 0, 0, 3,
		114, 32, 16, 0, 4, 0,
		0, 0, 101, 0, 0, 3,
		114, 32, 16, 0, 5, 0,
		0, 0, 101, 0, 0, 3,
		242, 32, 16, 0, 6, 0,
		0, 0, 101, 0, 0, 3,
		114, 32, 16, 0, 7, 0,
		0, 0, 104, 0, 0, 2,
		1, 0, 0, 0, 17, 0,
		0, 8, 18, 32, 16, 0,
		0, 0, 0, 0, 70, 30,
		16, 0, 0, 0, 0, 0,
		70, 142, 32, 0, 2, 0,
		0, 0, 4, 0, 0, 0,
		17, 0, 0, 8, 34, 32,
		16, 0, 0, 0, 0, 0,
		70, 30, 16, 0, 0, 0,
		0, 0, 70, 142, 32, 0,
		2, 0, 0, 0, 5, 0,
		0, 0, 17, 0, 0, 8,
		66, 32, 16, 0, 0, 0,
		0, 0, 70, 30, 16, 0,
		0, 0, 0, 0, 70, 142,
		32, 0, 2, 0, 0, 0,
		6, 0, 0, 0, 17, 0,
		0, 8, 130, 32, 16, 0,
		0, 0, 0, 0, 70, 30,
		16, 0, 0, 0, 0, 0,
		70, 142, 32, 0, 2, 0,
		0, 0, 7, 0, 0, 0,
		56, 0, 0, 8, 242, 32,
		16, 0, 1, 0, 0, 0,
		70, 30, 16, 0, 3, 0,
		0, 0, 70, 142, 32, 0,
		0, 0, 0, 0, 1, 0,
		0, 0, 54, 0, 0, 5,
		50, 0, 16, 0, 0, 0,
		0, 0, 70, 16, 16, 0,
		4, 0, 0, 0, 54, 0,
		0, 5, 66, 0, 16, 0,
		0, 0, 0, 0, 1, 64,
		0, 0, 0, 0, 128, 63,
		16, 0, 0, 8, 18, 32,
		16, 0, 2, 0, 0, 0,
		70, 2, 16, 0, 0, 0,
		0, 0, 70, 131, 32, 0,
		2, 0, 0, 0, 16, 0,
		0, 0, 16, 0, 0, 8,
		34, 32, 16, 0, 2, 0,
		0, 0, 70, 2, 16, 0,
		0, 0, 0, 0, 70, 131,
		32, 0, 2, 0, 0, 0,
		17, 0, 0, 0, 16, 0,
		0, 8, 18, 32, 16, 0,
		3, 0, 0, 0, 70, 18,
		16, 0, 1, 0, 0, 0,
		70, 130, 32, 0, 2, 0,
		0, 0, 0, 0, 0, 0,
		16, 0, 0, 8, 34, 32,
		16, 0, 3, 0, 0, 0,
		70, 18, 16, 0, 1, 0,
		0, 0, 70, 130, 32, 0,
		2, 0, 0, 0, 1, 0,
		0, 0, 16, 0, 0, 8,
		66, 32, 16, 0, 3, 0,
		0, 0, 70, 18, 16, 0,
		1, 0, 0, 0, 70, 130,
		32, 0, 2, 0, 0, 0,
		2, 0, 0, 0, 17, 0,
		0, 8, 18, 0, 16, 0,
		0, 0, 0, 0, 70, 30,
		16, 0, 0, 0, 0, 0,
		70, 142, 32, 0, 2, 0,
		0, 0, 0, 0, 0, 0,
		17, 0, 0, 8, 34, 0,
		16, 0, 0, 0, 0, 0,
		70, 30, 16, 0, 0, 0,
		0, 0, 70, 142, 32, 0,
		2, 0, 0, 0, 1, 0,
		0, 0, 17, 0, 0, 8,
		66, 0, 16, 0, 0, 0,
		0, 0, 70, 30, 16, 0,
		0, 0, 0, 0, 70, 142,
		32, 0, 2, 0, 0, 0,
		2, 0, 0, 0, 54, 0,
		0, 5, 114, 32, 16, 0,
		4, 0, 0, 0, 70, 2,
		16, 0, 0, 0, 0, 0,
		0, 0, 0, 9, 114, 32,
		16, 0, 5, 0, 0, 0,
		70, 2, 16, 128, 65, 0,
		0, 0, 0, 0, 0, 0,
		70, 130, 32, 0, 2, 0,
		0, 0, 20, 0, 0, 0,
		54, 0, 0, 5, 242, 32,
		16, 0, 6, 0, 0, 0,
		70, 30, 16, 0, 2, 0,
		0, 0, 54, 0, 0, 5,
		114, 32, 16, 0, 7, 0,
		0, 0, 70, 18, 16, 0,
		1, 0, 0, 0, 62, 0,
		0, 1, 83, 84, 65, 84,
		116, 0, 0, 0, 20, 0,
		0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 13, 0,
		0, 0, 14, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		82, 68, 69, 70, 216, 2,
		0, 0, 2, 0, 0, 0,
		116, 0, 0, 0, 2, 0,
		0, 0, 28, 0, 0, 0,
		0, 4, 254, 255, 0, 1,
		0, 0, 164, 2, 0, 0,
		92, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 0,
		0, 0, 105, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 2, 0,
		0, 0, 1, 0, 0, 0,
		1, 0, 0, 0, 77, 97,
		116, 101, 114, 105, 97, 108,
		86, 97, 114, 115, 0, 79,
		98, 106, 101, 99, 116, 86,
		97, 114, 115, 0, 92, 0,
		0, 0, 5, 0, 0, 0,
		164, 0, 0, 0, 80, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 105, 0,
		0, 0, 6, 0, 0, 0,
		148, 1, 0, 0, 80, 1,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 28, 1,
		0, 0, 0, 0, 0, 0,
		16, 0, 0, 0, 0, 0,
		0, 0, 44, 1, 0, 0,
		0, 0, 0, 0, 60, 1,
		0, 0, 16, 0, 0, 0,
		16, 0, 0, 0, 2, 0,
		0, 0, 44, 1, 0, 0,
		0, 0, 0, 0, 76, 1,
		0, 0, 32, 0, 0, 0,
		16, 0, 0, 0, 0, 0,
		0, 0, 44, 1, 0, 0,
		0, 0, 0, 0, 93, 1,
		0, 0, 48, 0, 0, 0,
		16, 0, 0, 0, 0, 0,
		0, 0, 44, 1, 0, 0,
		0, 0, 0, 0, 110, 1,
		0, 0, 64, 0, 0, 0,
		4, 0, 0, 0, 0, 0,
		0, 0, 132, 1, 0, 0,
		0, 0, 0, 0, 77, 97,
		116, 101, 114, 105, 97, 108,
		65, 109, 98, 105, 101, 110,
		116, 0, 1, 0, 3, 0,
		1, 0, 4, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		77, 97, 116, 101, 114, 105,
		97, 108, 68, 105, 102, 102,
		117, 115, 101, 0, 77, 97,
		116, 101, 114, 105, 97, 108,
		83, 112, 101, 99, 117, 108,
		97, 114, 0, 77, 97, 116,
		101, 114, 105, 97, 108, 69,
		109, 105, 115, 115, 105, 118,
		101, 0, 77, 97, 116, 101,
		114, 105, 97, 108, 83, 112,
		101, 99, 117, 108, 97, 114,
		80, 111, 119, 101, 114, 0,
		0, 0, 3, 0, 1, 0,
		1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 36, 2,
		0, 0, 0, 0, 0, 0,
		64, 0, 0, 0, 2, 0,
		0, 0, 52, 2, 0, 0,
		0, 0, 0, 0, 68, 2,
		0, 0, 64, 0, 0, 0,
		64, 0, 0, 0, 2, 0,
		0, 0, 52, 2, 0, 0,
		0, 0, 0, 0, 88, 2,
		0, 0, 128, 0, 0, 0,
		64, 0, 0, 0, 0, 0,
		0, 0, 52, 2, 0, 0,
		0, 0, 0, 0, 104, 2,
		0, 0, 192, 0, 0, 0,
		64, 0, 0, 0, 0, 0,
		0, 0, 52, 2, 0, 0,
		0, 0, 0, 0, 119, 2,
		0, 0, 0, 1, 0, 0,
		64, 0, 0, 0, 2, 0,
		0, 0, 52, 2, 0, 0,
		0, 0, 0, 0, 134, 2,
		0, 0, 64, 1, 0, 0,
		12, 0, 0, 0, 2, 0,
		0, 0, 148, 2, 0, 0,
		0, 0, 0, 0, 76, 111,
		99, 97, 108, 84, 111, 87,
		111, 114, 108, 100, 52, 120,
		52, 0, 3, 0, 3, 0,
		4, 0, 4, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		76, 111, 99, 97, 108, 84,
		111, 80, 114, 111, 106, 101,
		99, 116, 101, 100, 52, 120,
		52, 0, 87, 111, 114, 108,
		100, 84, 111, 76, 111, 99,
		97, 108, 52, 120, 52, 0,
		87, 111, 114, 108, 100, 84,
		111, 86, 105, 101, 119, 52,
		120, 52, 0, 85, 86, 84,
		114, 97, 110, 115, 102, 111,
		114, 109, 52, 120, 52, 0,
		69, 121, 101, 80, 111, 115,
		105, 116, 105, 111, 110, 0,
		171, 171, 1, 0, 3, 0,
		1, 0, 3, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		77, 105, 99, 114, 111, 115,
		111, 102, 116, 32, 40, 82,
		41, 32, 72, 76, 83, 76,
		32, 83, 104, 97, 100, 101,
		114, 32, 67, 111, 109, 112,
		105, 108, 101, 114, 32, 54,
		46, 51, 46, 57, 54, 48,
		48, 46, 49, 54, 51, 56,
		52, 0, 171, 171, 73, 83,
		71, 78, 168, 0, 0, 0,
		5, 0, 0, 0, 8, 0,
		0, 0, 128, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 0, 0,
		0, 0, 0, 0, 15, 15,
		0, 0, 137, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 0, 0,
		1, 0, 0, 0, 7, 7,
		0, 0, 144, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 0, 0,
		2, 0, 0, 0, 15, 15,
		0, 0, 152, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 0, 0,
		3, 0, 0, 0, 15, 15,
		0, 0, 158, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 3, 0, 0, 0,
		4, 0, 0, 0, 3, 3,
		0, 0, 80, 79, 83, 73,
		84, 73, 79, 78, 0, 78,
		79, 82, 77, 65, 76, 0,
		84, 65, 78, 71, 69, 78,
		84, 0, 67, 79, 76, 79,
		82, 0, 84, 69, 88, 67,
		79, 79, 82, 68, 0, 171,
		79, 83, 71, 78, 228, 0,
		0, 0, 8, 0, 0, 0,
		8, 0, 0, 0, 200, 0,
		0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 3, 0,
		0, 0, 0, 0, 0, 0,
		15, 0, 0, 0, 212, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 0,
		0, 0, 1, 0, 0, 0,
		15, 0, 0, 0, 218, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 0,
		0, 0, 2, 0, 0, 0,
		3, 12, 0, 0, 218, 0,
		0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 3, 0,
		0, 0, 3, 0, 0, 0,
		7, 8, 0, 0, 218, 0,
		0, 0, 2, 0, 0, 0,
		0, 0, 0, 0, 3, 0,
		0, 0, 4, 0, 0, 0,
		7, 8, 0, 0, 218, 0,
		0, 0, 3, 0, 0, 0,
		0, 0, 0, 0, 3, 0,
		0, 0, 5, 0, 0, 0,
		7, 8, 0, 0, 218, 0,
		0, 0, 4, 0, 0, 0,
		0, 0, 0, 0, 3, 0,
		0, 0, 6, 0, 0, 0,
		15, 0, 0, 0, 218, 0,
		0, 0, 5, 0, 0, 0,
		0, 0, 0, 0, 3, 0,
		0, 0, 7, 0, 0, 0,
		7, 8, 0, 0, 83, 86,
		95, 80, 79, 83, 73, 84,
		73, 79, 78, 0, 67, 79,
		76, 79, 82, 0, 84, 69,
		88, 67, 79, 79, 82, 68,
		0, 171
	};

	///////////////////////////////////////////////////////////////////////////////////////////
	//
	// Graphics wraps D3D engine and related constant buffers
	//
	class Graphics
	{
	public:
		// Construction / destruction.
		Graphics()
		{
		}

		~Graphics()
		{
			this->Shutdown();
		}

		// Initializes the Graphics object.
		void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, D3D_FEATURE_LEVEL deviceFeatureLevel)
		{
			// Make sure this is shutdown before initializing.
			this->Shutdown();

			// Store the device interfaces and feature level.
			m_device = device;
			m_deviceContext = deviceContext;
			m_deviceFeatureLevel = deviceFeatureLevel;

			// Create the constant buffers.
			D3D11_BUFFER_DESC bufferDesc;
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.CPUAccessFlags = 0;
			bufferDesc.MiscFlags = 0;
			bufferDesc.StructureByteStride = 0;

			bufferDesc.ByteWidth = sizeof(MaterialConstants);
			m_device->CreateBuffer(&bufferDesc, nullptr, &m_materialConstants);

			bufferDesc.ByteWidth = sizeof(LightConstants);
			m_device->CreateBuffer(&bufferDesc, nullptr, &m_lightConstants);

			bufferDesc.ByteWidth = sizeof(ObjectConstants);
			m_device->CreateBuffer(&bufferDesc, nullptr, &m_objectConstants);

			bufferDesc.ByteWidth = sizeof(MiscConstants);
			m_device->CreateBuffer(&bufferDesc, nullptr, &m_miscConstants);

			// Create the sampler state.
			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = m_deviceFeatureLevel <= D3D_FEATURE_LEVEL_9_1 ? 2 : 4;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			samplerDesc.BorderColor[0] = 0.0f;
			samplerDesc.BorderColor[1] = 0.0f;
			samplerDesc.BorderColor[2] = 0.0f;
			samplerDesc.BorderColor[3] = 0.0f;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
			m_device->CreateSamplerState(&samplerDesc, &m_sampler);

			// Create the vertex layout.
			D3D11_INPUT_ELEMENT_DESC layout [] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			m_device->CreateInputLayout(layout, _countof(layout), VSD3DStarter_VS, _countof(VSD3DStarter_VS), &m_vertexLayout);

			// Create the vertex shader.
			m_device->CreateVertexShader(VSD3DStarter_VS, _countof(VSD3DStarter_VS), nullptr, &m_vertexShader);

			// Create the null texture (a 1x1 white texture so shaders work when textures are not set on meshes correctly).
			D3D11_TEXTURE2D_DESC desc;
			desc.Width = 1;
			desc.Height = 1;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			m_device->CreateTexture2D(&desc, nullptr, &m_nullTexture);

			INT32 white = 0xffffffff;
			m_deviceContext->UpdateSubresource(m_nullTexture.Get(), 0, nullptr, &white, sizeof(white), sizeof(white));

			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> nullTextureView;
			m_device->CreateShaderResourceView(m_nullTexture.Get(), nullptr, &nullTextureView);
			m_textureResources[L""] = nullTextureView;
		}

		// Shuts down the Graphics object.
		void Shutdown()
		{
			m_pixelShaderResources.clear();
			m_textureResources.clear();
		}

		// Accessors.
		Camera& GetCamera() const { return m_camera; }

		ID3D11Device* GetDevice() const { return m_device.Get(); }
		ID3D11DeviceContext* GetDeviceContext() const { return m_deviceContext.Get(); }
		D3D_FEATURE_LEVEL GetDeviceFeatureLevel() const { return m_deviceFeatureLevel; }

		ID3D11Buffer* GetMaterialConstants() const { return m_materialConstants.Get(); }
		ID3D11Buffer* GetLightConstants() const { return m_lightConstants.Get(); }
		ID3D11Buffer* GetObjectConstants() const { return m_objectConstants.Get(); }
		ID3D11Buffer* GetMiscConstants() const { return m_miscConstants.Get(); }

		ID3D11SamplerState* GetSamplerState() const { return m_sampler.Get(); }
		ID3D11InputLayout* GetVertexInputLayout() const { return m_vertexLayout.Get(); }
		ID3D11VertexShader* GetVertexShader() const { return m_vertexShader.Get(); }

		concurrency::task<ID3D11PixelShader*> GetOrCreatePixelShaderAsync(const std::wstring& shaderName)
		{
			auto iter = m_pixelShaderResources.find(shaderName);
			if (iter != m_pixelShaderResources.end())
			{
				return concurrency::extras::create_value_task(iter->second.Get());
			}
			else
			{
				std::vector<BYTE> psBuffer;
				return DX::ReadDataAsync(shaderName).then([this, shaderName](const std::vector<byte>& psBuffer) -> ID3D11PixelShader*
				{
					Microsoft::WRL::ComPtr<ID3D11PixelShader> result = nullptr;

					if (psBuffer.size() > 0)
					{
						this->GetDevice()->CreatePixelShader(&psBuffer[0], psBuffer.size(), nullptr, result.GetAddressOf());
						if (result == nullptr)
						{
							throw std::exception("Pixel Shader could not be created");
						}

						m_pixelShaderResources[shaderName] = result;

						return result.Get();
					}
					else
					{
						return nullptr;
					}
				});
			}
		}

		concurrency::task<ID3D11ShaderResourceView*> GetOrCreateTextureAsync(const std::wstring& textureName)
		{
			auto iter = m_textureResources.find(textureName);
			if (iter != m_textureResources.end())
			{
				return concurrency::extras::create_value_task(iter->second.Get());
			}
			else
			{
				std::vector<BYTE> ddsBuffer;
				return DX::ReadDataAsync(textureName).then([this, textureName](const std::vector<byte>& ddsBuffer) -> ID3D11ShaderResourceView*
				{
					if (ddsBuffer.size() > 0)
					{
						Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> result(this->CreateTextureFromDDSInMemory(&ddsBuffer[0], ddsBuffer.size()));
						if (result == nullptr)
						{
							throw std::exception("Texture could not be created");
						}
						m_textureResources[textureName] = result;

						return result.Get();
					}
					else
					{
						return nullptr;
					}
				});
			}
		}

		// Methods to update constant buffers.
		void UpdateMaterialConstants(const MaterialConstants& data) const
		{
			m_deviceContext->UpdateSubresource(m_materialConstants.Get(), 0, nullptr, &data, 0, 0);
		}
		void UpdateLightConstants(const LightConstants& data) const
		{
			m_deviceContext->UpdateSubresource(m_lightConstants.Get(), 0, nullptr, &data, 0, 0);
		}
		void UpdateObjectConstants(const ObjectConstants& data) const
		{
			m_deviceContext->UpdateSubresource(m_objectConstants.Get(), 0, nullptr, &data, 0, 0);
		}
		void UpdateMiscConstants(const MiscConstants& data) const
		{
			m_deviceContext->UpdateSubresource(m_miscConstants.Get(), 0, nullptr, &data, 0, 0);
		}

	private:
		ID3D11ShaderResourceView* CreateTextureFromDDSInMemory(const BYTE* ddsData, size_t ddsDataSize)
		{
			ID3D11ShaderResourceView* textureView = nullptr;

			if (ddsData != nullptr && ddsDataSize > 0)
			{
				HRESULT hr = DirectX::CreateDDSTextureFromMemory(m_device.Get(), ddsData, ddsDataSize, nullptr, &textureView);

				if (FAILED(hr))
				{
					SafeRelease(textureView);
				}
				else
				{
					return textureView;
				}
			}

			return nullptr;
		}

		std::map<std::wstring, Microsoft::WRL::ComPtr<ID3D11PixelShader>> m_pixelShaderResources;
		std::map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureResources;

		mutable Camera m_camera;

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
		D3D_FEATURE_LEVEL m_deviceFeatureLevel;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_materialConstants;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_lightConstants;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_objectConstants;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_miscConstants;

		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_vertexLayout;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_nullTexture;
	};

}