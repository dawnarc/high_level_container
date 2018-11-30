// Fill out your copyright notice in the Description page of Project Settings.

#include "VarObject.h"

VarObject::VarObject()
{
	ValType_ = EValueType::None;

	IntVal_ = 0;
	FloatVal_ = 0.f;
	StrVal_ = TEXT("");
	ObjVal_ = NULL;
}

VarObject::VarObject(int Val)
{
	ValType_ = EValueType::Integer;
	IntVal_ = Val;
}

VarObject::VarObject(float Val)
{
	ValType_ = EValueType::Float;
	FloatVal_ = Val;
}

VarObject::VarObject(const FString& Val)
{
	ValType_ = EValueType::String;
	StrVal_ = (FString&)Val;
}

VarObject::VarObject(const UObject* Val)
{
	ValType_ = EValueType::Object;
	ObjVal_ = (UObject*)Val;
}

VarObject::~VarObject()
{
}

//void VarObject::SetValue(int Val)
//{
//	ValType = EValueType::Integer;
//	IntVal = Val;
//}
//
//void VarObject::SetValue(float Val)
//{
//	ValType = EValueType::Float;
//	FloatVal = Val;
//}
//
//void VarObject::SetValue(const FString& Val)
//{
//	ValType = EValueType::String;
//	StrVal = Val;
//}
//
//void VarObject::SetValue(UObject* Val)
//{
//	ValType = EValueType::Object;
//	ObjVal = Val;
//}