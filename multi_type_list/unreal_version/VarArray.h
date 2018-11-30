// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "VarObject.h"

/**
 * 
 */
class VarArray
{
public:
	VarArray();
	~VarArray();

	void AddValue(int Val);
	void AddValue(float Val);
	void AddValue(const FString& Val);
	void AddValue(const UObject* Val);

	VarObject GetValue(int Index) const;
	void RemoveValue(int Index);
	int Size() const;

	int PopInt() const;
	float PopFloat() const;
	FString PopString() const;
	UObject* PopObject() const;


private:

	mutable std::vector<VarObject> Values;
};
