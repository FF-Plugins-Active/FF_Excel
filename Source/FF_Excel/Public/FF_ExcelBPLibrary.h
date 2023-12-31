/*
*	Xlnt Library.
*	https://github.com/tfussell/xlnt
* 
*	Xlnt Documentations.
*	https://tfussell.gitbooks.io/xlnt/content/
* 
*/
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "FF_Excel_Enums.h"

THIRD_PARTY_INCLUDES_START
#include "xlnt.hpp"
THIRD_PARTY_INCLUDES_END

#include "FF_ExcelBPLibrary.generated.h"

UCLASS(BlueprintType)
class FF_EXCEL_API UFFExcel_Xlnt_Doc : public UObject
{
	GENERATED_BODY()

public:

	xlnt::workbook Document;

};

UCLASS(BlueprintType)
class FF_EXCEL_API UFFExcel_Xlnt_Worksheet : public UObject
{
	GENERATED_BODY()

public:

	xlnt::worksheet Worksheet;

};

UCLASS(BlueprintType)
class FF_EXCEL_API UFFExcel_Xlnt_Cell : public UObject
{
	GENERATED_BODY()

public:

	xlnt::cell Cell;

};

USTRUCT(BlueprintType)
struct FF_EXCEL_API FXlntWorksheetProperties
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	UFFExcel_Xlnt_Worksheet* Worksheet_Object = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FString Title = "";

	UPROPERTY(BlueprintReadWrite)
	int32 Id = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Index = 0;

	bool operator == (const FXlntWorksheetProperties& Other) const
	{
		return Title == Other.Title && Id == Other.Id && Index == Other.Index;
	}

	bool operator != (const FXlntWorksheetProperties& Other) const
	{
		return !(*this == Other);
	}
};

FORCEINLINE uint32 GetTypeHash(const FXlntWorksheetProperties& Key)
{
	uint32 Hash_Title = GetTypeHash(Key.Title);
	uint32 Hash_Id = GetTypeHash(Key.Id);
	uint32 Hash_Index = GetTypeHash(Key.Index);

	uint32 GenericHash;
	FMemory::Memset(&GenericHash, 0, sizeof(uint32));
	GenericHash = HashCombine(GenericHash, Hash_Title);
	GenericHash = HashCombine(GenericHash, Hash_Id);
	GenericHash = HashCombine(GenericHash, Hash_Index);

	return GenericHash;
}

USTRUCT(BlueprintType)
struct FF_EXCEL_API FXlntCellProperties
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	UFFExcel_Xlnt_Cell* Cell_Object = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FString Position_String = "";

	UPROPERTY(BlueprintReadWrite)
	FVector2D Position_Referance = FVector2D(0.f, 0.f);

	UPROPERTY(BlueprintReadWrite)
	EXlntDataTypes ValueType = EXlntDataTypes::None;

	bool operator == (const FXlntCellProperties& Other) const
	{
		return Position_String == Other.Position_String && Position_Referance == Other.Position_Referance;
	}

	bool operator != (const FXlntCellProperties& Other) const
	{
		return !(*this == Other);
	}
};

FORCEINLINE uint32 GetTypeHash(const FXlntCellProperties& Key)
{
	uint32 Hash_Position_String = GetTypeHash(Key.Position_String);
	uint32 Hash_Position_Referance = GetTypeHash(Key.Position_Referance);

	uint32 GenericHash;
	FMemory::Memset(&GenericHash, 0, sizeof(uint32));
	GenericHash = HashCombine(GenericHash, Hash_Position_String);
	GenericHash = HashCombine(GenericHash, Hash_Position_Referance);

	return GenericHash;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateXlntSheets, bool, IsSuccessfull, const TArray<FXlntWorksheetProperties>&, Out_Sheets);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateXlntCells, bool, IsSuccessfull, const TArray<FXlntCellProperties>&, Out_Cells);

UCLASS()
class UFF_ExcelBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Open Excel from File", Keywords = "xlnt, excel, open, file"), Category = "FF_Excel|xlnt|Document")
	static FF_EXCEL_API bool XLNT_Open_Excel_File(UFFExcel_Xlnt_Doc*& Out_Doc, FString In_Path, FString Password = "");

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Open Excel from Memory", Keywords = "xlnt, excel, open, file"), Category = "FF_Excel|xlnt|Document")
	static FF_EXCEL_API bool XLNT_Open_Excel_Memory(UFFExcel_Xlnt_Doc*& Out_Doc, TArray<uint8> In_Buffer, FString FileName = "", FString Password = "");

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Get All Worksheets", Keywords = "xlnt, excel, work, sheet, worksheet, get, all"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API void XLNT_Worksheets_Get_All(FDelegateXlntSheets DelegateSheets, UFFExcel_Xlnt_Doc* In_Doc);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Get Worksheet by Title", Keywords = "xlnt, excel, work, sheet, worksheet, get, by, title, name"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API bool XLNT_Worksheet_Get_By_Title(UFFExcel_Xlnt_Worksheet*& Out_Sheet, UFFExcel_Xlnt_Doc* In_Doc, FString In_Title);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Get Worksheet by Id", Keywords = "xlnt, excel, work, sheet, worksheet, get, by, id"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API bool XLNT_Worksheet_Get_By_Id(UFFExcel_Xlnt_Worksheet*& Out_Sheet, UFFExcel_Xlnt_Doc* In_Doc, int32 In_Id);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Get Worksheet by Index", Keywords = "xlnt, excel, work, sheet, worksheet, get, by, index"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API bool XLNT_Worksheet_Get_By_Index(UFFExcel_Xlnt_Worksheet*& Out_Sheet, UFFExcel_Xlnt_Doc* In_Doc, int32 In_Index);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Worksheet Name", Keywords = "xlnt, excel, work, sheet, worksheet, get, name, title"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API bool XLNT_Worksheet_Get_Title(FString& Out_Title, UFFExcel_Xlnt_Worksheet* In_Sheet);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Worksheet Id", Keywords = "xlnt, excel, work, sheet, worksheet, get, id"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API bool XLNT_Worksheet_Get_Id(int32& Out_Id, UFFExcel_Xlnt_Worksheet* In_Sheet);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Worksheet Index", Keywords = "xlnt, excel, work, sheet, worksheet, get, index"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API bool XLNT_Worksheet_Get_Index(int32& Out_Index, UFFExcel_Xlnt_Worksheet* In_Sheet);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Worksheet Borders", Keywords = "xlnt, excel, cell, get, value, type"), Category = "FF_Excel|xlnt|Worksheets")
	static FF_EXCEL_API bool XLNT_Worksheet_Get_Borders(int32& Highest_Column, int32& Lowest_Column, int32& Highest_Row, int32& Lowest_Row, UFFExcel_Xlnt_Worksheet* In_Sheet = nullptr);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Get Cells at Column", Keywords = "xlnt, excel, work, sheet, worksheet, get, all, cell, cells, column"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API void XLNT_Cells_At_Column(FDelegateXlntCells DelegateCells, UFFExcel_Xlnt_Worksheet* In_Sheet, int32 Index_Column);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Get Cells at Row", Keywords = "xlnt, excel, work, sheet, worksheet, get, all, cell, cells, row"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API void XLNT_Cells_At_Row(FDelegateXlntCells DelegateCells, UFFExcel_Xlnt_Worksheet* In_Sheet, int32 Index_Row);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "XLNT - Get Cells All", Keywords = "xlnt, excel, work, sheet, worksheet, get, all, cell, cells"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API void XLNT_Cells_All(FDelegateXlntCells DelegateCells, UFFExcel_Xlnt_Worksheet* In_Sheet);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Value Type", Keywords = "xlnt, excel, cell, get, value, type"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API bool XLNT_Cell_Get_Value_Type(EXlntDataTypes& Out_Types, UFFExcel_Xlnt_Cell* In_Cell = nullptr);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Value as String", Keywords = "xlnt, excel, cell, get, value, string"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API bool XLNT_Cell_Get_Value_As_String(FString& Out_Value, UFFExcel_Xlnt_Cell* In_Cell);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Value as Integer", Keywords = "xlnt, excel, cell, get, value, int32"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API bool XLNT_Cell_Get_Value_As_Integer(int64& Out_Value, UFFExcel_Xlnt_Cell* In_Cell);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Value as Double", Keywords = "xlnt, excel, cell, get, value, double, float"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API bool XLNT_Cell_Get_Value_As_Double(double& Out_Value, UFFExcel_Xlnt_Cell* In_Cell);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Value as Date", Keywords = "xlnt, excel, cell, get, value, date"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API bool XLNT_Cell_Get_Value_As_Date(FDateTime& Out_Value, UFFExcel_Xlnt_Cell* In_Cell);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "XLNT - Get Value as Bool", Keywords = "xlnt, excel, cell, get, value, bool"), Category = "FF_Excel|xlnt|Cells")
	static FF_EXCEL_API bool XLNT_Cell_Get_Value_As_Bool(bool& Out_Value, UFFExcel_Xlnt_Cell* In_Cell);

};
