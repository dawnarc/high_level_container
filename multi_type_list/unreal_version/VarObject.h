// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum EValueType
{
	Integer,
	Float,
	String,
	Object,
	None,
};

/**
 * 
 */
class TOWERDEFENSE_API VarObject
{
public:
	VarObject();

	VarObject(int Val);
	VarObject(float Val);
	VarObject(const FString& Val);
	VarObject(const UObject* Val);

	~VarObject();

	EValueType ValueType() { return ValType_; };

	int IntVal() { return IntVal_; };

	float FloatVal() { return FloatVal_; };

	FString& StrVal() { return StrVal_; };

	UObject* ObjVal() { return ObjVal_; }

	/*void SetValue(int Val);
	void SetValue(float Val);
	void SetValue(const FString& Val);
	void SetValue(UObject* Val);*/
	
private:

	EValueType ValType_;

	int IntVal_;
	float FloatVal_;
	FString StrVal_;
	UObject* ObjVal_;
};
