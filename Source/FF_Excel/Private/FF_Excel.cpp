// Copyright Epic Games, Inc. All Rights Reserved.

#include "FF_Excel.h"

#define LOCTEXT_NAMESPACE "FFF_ExcelModule"

void FFF_ExcelModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FFF_ExcelModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFF_ExcelModule, FF_Excel)