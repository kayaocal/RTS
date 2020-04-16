// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef RTS_RTSGameModeBase_generated_h
#error "RTSGameModeBase.generated.h already included, missing '#pragma once' in RTSGameModeBase.h"
#endif
#define RTS_RTSGameModeBase_generated_h

#define RTS_Source_RTS_RTSGameModeBase_h_15_SPARSE_DATA
#define RTS_Source_RTS_RTSGameModeBase_h_15_RPC_WRAPPERS
#define RTS_Source_RTS_RTSGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define RTS_Source_RTS_RTSGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARTSGameModeBase(); \
	friend struct Z_Construct_UClass_ARTSGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ARTSGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/RTS"), NO_API) \
	DECLARE_SERIALIZER(ARTSGameModeBase)


#define RTS_Source_RTS_RTSGameModeBase_h_15_INCLASS \
private: \
	static void StaticRegisterNativesARTSGameModeBase(); \
	friend struct Z_Construct_UClass_ARTSGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ARTSGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/RTS"), NO_API) \
	DECLARE_SERIALIZER(ARTSGameModeBase)


#define RTS_Source_RTS_RTSGameModeBase_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ARTSGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ARTSGameModeBase) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARTSGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARTSGameModeBase); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARTSGameModeBase(ARTSGameModeBase&&); \
	NO_API ARTSGameModeBase(const ARTSGameModeBase&); \
public:


#define RTS_Source_RTS_RTSGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ARTSGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ARTSGameModeBase(ARTSGameModeBase&&); \
	NO_API ARTSGameModeBase(const ARTSGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARTSGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARTSGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ARTSGameModeBase)


#define RTS_Source_RTS_RTSGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET
#define RTS_Source_RTS_RTSGameModeBase_h_12_PROLOG
#define RTS_Source_RTS_RTSGameModeBase_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RTS_Source_RTS_RTSGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	RTS_Source_RTS_RTSGameModeBase_h_15_SPARSE_DATA \
	RTS_Source_RTS_RTSGameModeBase_h_15_RPC_WRAPPERS \
	RTS_Source_RTS_RTSGameModeBase_h_15_INCLASS \
	RTS_Source_RTS_RTSGameModeBase_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define RTS_Source_RTS_RTSGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RTS_Source_RTS_RTSGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	RTS_Source_RTS_RTSGameModeBase_h_15_SPARSE_DATA \
	RTS_Source_RTS_RTSGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	RTS_Source_RTS_RTSGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	RTS_Source_RTS_RTSGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RTS_API UClass* StaticClass<class ARTSGameModeBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID RTS_Source_RTS_RTSGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
