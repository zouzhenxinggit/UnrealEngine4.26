// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2017 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#include "ClothingCookedParam_0p1.h"
#include <string.h>
#include <stdlib.h>

using namespace NvParameterized;

namespace nvidia
{
namespace parameterized
{

using namespace ClothingCookedParam_0p1NS;

const char* const ClothingCookedParam_0p1Factory::vptr =
    NvParameterized::getVptr<ClothingCookedParam_0p1, ClothingCookedParam_0p1::ClassAlignment>();

const uint32_t NumParamDefs = 16;
static NvParameterized::DefinitionImpl* ParamDefTable; // now allocated in buildTree [NumParamDefs];


static const size_t ParamLookupChildrenTable[] =
{
	1, 2, 4, 6, 13, 15, 3, 5, 7, 8, 9, 10, 11, 12, 14,
};

#define TENUM(type) nvidia::##type
#define CHILDREN(index) &ParamLookupChildrenTable[index]
static const NvParameterized::ParamLookupNode ParamLookupTable[NumParamDefs] =
{
	{ TYPE_STRUCT, false, 0, CHILDREN(0), 6 },
	{ TYPE_F32, false, (size_t)(&((ParametersStruct*)0)->actorScale), NULL, 0 }, // actorScale
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->convexCookedData), CHILDREN(6), 1 }, // convexCookedData
	{ TYPE_U8, false, 1 * sizeof(uint8_t), NULL, 0 }, // convexCookedData[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->convexMeshPointers), CHILDREN(7), 1 }, // convexMeshPointers
	{ TYPE_POINTER, false, 1 * sizeof(void*), NULL, 0 }, // convexMeshPointers[]
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->cookedPhysicalSubmeshes), CHILDREN(8), 1 }, // cookedPhysicalSubmeshes
	{ TYPE_STRUCT, false, 1 * sizeof(CookedPhysicalSubmesh_Type), CHILDREN(9), 5 }, // cookedPhysicalSubmeshes[]
	{ TYPE_U32, false, (size_t)(&((CookedPhysicalSubmesh_Type*)0)->physicalMeshId), NULL, 0 }, // cookedPhysicalSubmeshes[].physicalMeshId
	{ TYPE_U32, false, (size_t)(&((CookedPhysicalSubmesh_Type*)0)->submeshId), NULL, 0 }, // cookedPhysicalSubmeshes[].submeshId
	{ TYPE_U32, false, (size_t)(&((CookedPhysicalSubmesh_Type*)0)->cookedDataOffset), NULL, 0 }, // cookedPhysicalSubmeshes[].cookedDataOffset
	{ TYPE_U32, false, (size_t)(&((CookedPhysicalSubmesh_Type*)0)->cookedDataLength), NULL, 0 }, // cookedPhysicalSubmeshes[].cookedDataLength
	{ TYPE_POINTER, false, (size_t)(&((CookedPhysicalSubmesh_Type*)0)->deformableMeshPointer), NULL, 0 }, // cookedPhysicalSubmeshes[].deformableMeshPointer
	{ TYPE_ARRAY, true, (size_t)(&((ParametersStruct*)0)->deformableCookedData), CHILDREN(14), 1 }, // deformableCookedData
	{ TYPE_U8, false, 1 * sizeof(uint8_t), NULL, 0 }, // deformableCookedData[]
	{ TYPE_U32, false, (size_t)(&((ParametersStruct*)0)->cookedDataVersion), NULL, 0 }, // cookedDataVersion
};


bool ClothingCookedParam_0p1::mBuiltFlag = false;
NvParameterized::MutexType ClothingCookedParam_0p1::mBuiltFlagMutex;

ClothingCookedParam_0p1::ClothingCookedParam_0p1(NvParameterized::Traits* traits, void* buf, int32_t* refCount) :
	NvParameters(traits, buf, refCount)
{
	//mParameterizedTraits->registerFactory(className(), &ClothingCookedParam_0p1FactoryInst);

	if (!buf) //Do not init data if it is inplace-deserialized
	{
		initDynamicArrays();
		initStrings();
		initReferences();
		initDefaults();
	}
}

ClothingCookedParam_0p1::~ClothingCookedParam_0p1()
{
	freeStrings();
	freeReferences();
	freeDynamicArrays();
}

void ClothingCookedParam_0p1::destroy()
{
	// We cache these fields here to avoid overwrite in destructor
	bool doDeallocateSelf = mDoDeallocateSelf;
	NvParameterized::Traits* traits = mParameterizedTraits;
	int32_t* refCount = mRefCount;
	void* buf = mBuffer;

	this->~ClothingCookedParam_0p1();

	NvParameters::destroy(this, traits, doDeallocateSelf, refCount, buf);
}

const NvParameterized::DefinitionImpl* ClothingCookedParam_0p1::getParameterDefinitionTree(void)
{
	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

const NvParameterized::DefinitionImpl* ClothingCookedParam_0p1::getParameterDefinitionTree(void) const
{
	ClothingCookedParam_0p1* tmpParam = const_cast<ClothingCookedParam_0p1*>(this);

	if (!mBuiltFlag) // Double-checked lock
	{
		NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);
		if (!mBuiltFlag)
		{
			tmpParam->buildTree();
		}
	}

	return(&ParamDefTable[0]);
}

NvParameterized::ErrorType ClothingCookedParam_0p1::getParameterHandle(const char* long_name, Handle& handle) const
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

NvParameterized::ErrorType ClothingCookedParam_0p1::getParameterHandle(const char* long_name, Handle& handle)
{
	ErrorType Ret = NvParameters::getParameterHandle(long_name, handle);
	if (Ret != ERROR_NONE)
	{
		return(Ret);
	}

	size_t offset;
	void* ptr;

	getVarPtr(handle, ptr, offset);

	if (ptr == NULL)
	{
		return(ERROR_INDEX_OUT_OF_RANGE);
	}

	return(ERROR_NONE);
}

void ClothingCookedParam_0p1::getVarPtr(const Handle& handle, void*& ptr, size_t& offset) const
{
	ptr = getVarPtrHelper(&ParamLookupTable[0], const_cast<ClothingCookedParam_0p1::ParametersStruct*>(&parameters()), handle, offset);
}


/* Dynamic Handle Indices */

void ClothingCookedParam_0p1::freeParameterDefinitionTable(NvParameterized::Traits* traits)
{
	if (!traits)
	{
		return;
	}

	if (!mBuiltFlag) // Double-checked lock
	{
		return;
	}

	NvParameterized::MutexType::ScopedLock lock(mBuiltFlagMutex);

	if (!mBuiltFlag)
	{
		return;
	}

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		ParamDefTable[i].~DefinitionImpl();
	}

	traits->free(ParamDefTable);

	mBuiltFlag = false;
}

#define PDEF_PTR(index) (&ParamDefTable[index])

void ClothingCookedParam_0p1::buildTree(void)
{

	uint32_t allocSize = sizeof(NvParameterized::DefinitionImpl) * NumParamDefs;
	ParamDefTable = (NvParameterized::DefinitionImpl*)(mParameterizedTraits->alloc(allocSize));
	memset(ParamDefTable, 0, allocSize);

	for (uint32_t i = 0; i < NumParamDefs; ++i)
	{
		NV_PARAM_PLACEMENT_NEW(ParamDefTable + i, NvParameterized::DefinitionImpl)(*mParameterizedTraits);
	}

	// Initialize DefinitionImpl node: nodeIndex=0, longName=""
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[0];
		ParamDef->init("", TYPE_STRUCT, "STRUCT", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=1, longName="actorScale"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[1];
		ParamDef->init("actorScale", TYPE_F32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=2, longName="convexCookedData"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[2];
		ParamDef->init("convexCookedData", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "All convexes are checked into the same buffer, one after the other.\n", true);
		HintTable[1].init("shortDescription", "The cooked data for all the convex meshes.", true);
		ParamDefTable[2].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=3, longName="convexCookedData[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[3];
		ParamDef->init("convexCookedData", TYPE_U8, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "All convexes are checked into the same buffer, one after the other.\n", true);
		HintTable[1].init("shortDescription", "The cooked data for all the convex meshes.", true);
		ParamDefTable[3].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=4, longName="convexMeshPointers"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[4];
		ParamDef->init("convexMeshPointers", TYPE_ARRAY, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", uint64_t(1), true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", uint64_t(1), true);
		ParamDefTable[4].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */




		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=5, longName="convexMeshPointers[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[5];
		ParamDef->init("convexMeshPointers", TYPE_POINTER, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", uint64_t(1), true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", uint64_t(1), true);
		ParamDefTable[5].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=6, longName="cookedPhysicalSubmeshes"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[6];
		ParamDef->init("cookedPhysicalSubmeshes", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=7, longName="cookedPhysicalSubmeshes[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[7];
		ParamDef->init("cookedPhysicalSubmeshes", TYPE_STRUCT, "CookedPhysicalSubmesh", true);






	}

	// Initialize DefinitionImpl node: nodeIndex=8, longName="cookedPhysicalSubmeshes[].physicalMeshId"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[8];
		ParamDef->init("physicalMeshId", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=9, longName="cookedPhysicalSubmeshes[].submeshId"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[9];
		ParamDef->init("submeshId", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=10, longName="cookedPhysicalSubmeshes[].cookedDataOffset"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[10];
		ParamDef->init("cookedDataOffset", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=11, longName="cookedPhysicalSubmeshes[].cookedDataLength"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[11];
		ParamDef->init("cookedDataLength", TYPE_U32, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=12, longName="cookedPhysicalSubmeshes[].deformableMeshPointer"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[12];
		ParamDef->init("deformableMeshPointer", TYPE_POINTER, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", uint64_t(1), true);
		ParamDefTable[12].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#else

		static HintImpl HintTable[1];
		static Hint* HintPtrTable[1] = { &HintTable[0], };
		HintTable[0].init("DONOTSERIALIZE", uint64_t(1), true);
		ParamDefTable[12].setHints((const NvParameterized::Hint**)HintPtrTable, 1);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// Initialize DefinitionImpl node: nodeIndex=13, longName="deformableCookedData"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[13];
		ParamDef->init("deformableCookedData", TYPE_ARRAY, NULL, true);





		ParamDef->setArraySize(-1);
	}

	// Initialize DefinitionImpl node: nodeIndex=14, longName="deformableCookedData[]"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[14];
		ParamDef->init("deformableCookedData", TYPE_U8, NULL, true);






	}

	// Initialize DefinitionImpl node: nodeIndex=15, longName="cookedDataVersion"
	{
		NvParameterized::DefinitionImpl* ParamDef = &ParamDefTable[15];
		ParamDef->init("cookedDataVersion", TYPE_U32, NULL, true);

#ifdef NV_PARAMETERIZED_HIDE_DESCRIPTIONS

#else

		static HintImpl HintTable[2];
		static Hint* HintPtrTable[2] = { &HintTable[0], &HintTable[1], };
		HintTable[0].init("longDescription", "When loading into a different PhysX version, it will cook again on loading.", true);
		HintTable[1].init("shortDescription", "The PhysX SDK Version this data was cooked from", true);
		ParamDefTable[15].setHints((const NvParameterized::Hint**)HintPtrTable, 2);

#endif /* NV_PARAMETERIZED_HIDE_DESCRIPTIONS */





	}

	// SetChildren for: nodeIndex=0, longName=""
	{
		static Definition* Children[6];
		Children[0] = PDEF_PTR(1);
		Children[1] = PDEF_PTR(2);
		Children[2] = PDEF_PTR(4);
		Children[3] = PDEF_PTR(6);
		Children[4] = PDEF_PTR(13);
		Children[5] = PDEF_PTR(15);

		ParamDefTable[0].setChildren(Children, 6);
	}

	// SetChildren for: nodeIndex=2, longName="convexCookedData"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(3);

		ParamDefTable[2].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=4, longName="convexMeshPointers"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(5);

		ParamDefTable[4].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=6, longName="cookedPhysicalSubmeshes"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(7);

		ParamDefTable[6].setChildren(Children, 1);
	}

	// SetChildren for: nodeIndex=7, longName="cookedPhysicalSubmeshes[]"
	{
		static Definition* Children[5];
		Children[0] = PDEF_PTR(8);
		Children[1] = PDEF_PTR(9);
		Children[2] = PDEF_PTR(10);
		Children[3] = PDEF_PTR(11);
		Children[4] = PDEF_PTR(12);

		ParamDefTable[7].setChildren(Children, 5);
	}

	// SetChildren for: nodeIndex=13, longName="deformableCookedData"
	{
		static Definition* Children[1];
		Children[0] = PDEF_PTR(14);

		ParamDefTable[13].setChildren(Children, 1);
	}

	mBuiltFlag = true;

}
void ClothingCookedParam_0p1::initStrings(void)
{
}

void ClothingCookedParam_0p1::initDynamicArrays(void)
{
	convexCookedData.buf = NULL;
	convexCookedData.isAllocated = true;
	convexCookedData.elementSize = sizeof(uint8_t);
	convexCookedData.arraySizes[0] = 0;
	convexMeshPointers.buf = NULL;
	convexMeshPointers.isAllocated = true;
	convexMeshPointers.elementSize = sizeof(void*);
	convexMeshPointers.arraySizes[0] = 0;
	cookedPhysicalSubmeshes.buf = NULL;
	cookedPhysicalSubmeshes.isAllocated = true;
	cookedPhysicalSubmeshes.elementSize = sizeof(CookedPhysicalSubmesh_Type);
	cookedPhysicalSubmeshes.arraySizes[0] = 0;
	deformableCookedData.buf = NULL;
	deformableCookedData.isAllocated = true;
	deformableCookedData.elementSize = sizeof(uint8_t);
	deformableCookedData.arraySizes[0] = 0;
}

void ClothingCookedParam_0p1::initDefaults(void)
{

	freeStrings();
	freeReferences();
	freeDynamicArrays();
	actorScale = float(1.0f);
	cookedDataVersion = uint32_t(0);

	initDynamicArrays();
	initStrings();
	initReferences();
}

void ClothingCookedParam_0p1::initReferences(void)
{
}

void ClothingCookedParam_0p1::freeDynamicArrays(void)
{
	if (convexCookedData.isAllocated && convexCookedData.buf)
	{
		mParameterizedTraits->free(convexCookedData.buf);
	}
	if (convexMeshPointers.isAllocated && convexMeshPointers.buf)
	{
		mParameterizedTraits->free(convexMeshPointers.buf);
	}
	if (cookedPhysicalSubmeshes.isAllocated && cookedPhysicalSubmeshes.buf)
	{
		mParameterizedTraits->free(cookedPhysicalSubmeshes.buf);
	}
	if (deformableCookedData.isAllocated && deformableCookedData.buf)
	{
		mParameterizedTraits->free(deformableCookedData.buf);
	}
}

void ClothingCookedParam_0p1::freeStrings(void)
{
}

void ClothingCookedParam_0p1::freeReferences(void)
{
}

} // namespace parameterized
} // namespace nvidia