// Fill out your copyright notice in the Description page of Project Settings.

#include "VarArray.h"

VarArray::VarArray()
{
}

VarArray::~VarArray()
{
}

void VarArray::AddValue(int Val)
{
	VarObject Var(Val);
	Values.push_back(Var);
}

void VarArray::AddValue(float Val)
{
	VarObject Var(Val);
	Values.push_back(Var);
}

void VarArray::AddValue(const FString& Val)
{
	VarObject Var(Val);
	Values.push_back(Var);
}

void VarArray::AddValue(const UObject* Val)
{
	VarObject Var(Val);
	Values.push_back(Var);
}

VarObject VarArray::GetValue(int Index) const
{
	if (Index < 0 || Index >= Values.size())
	{
		return VarObject();
	}

	return Values.at(Index);
}

void VarArray::RemoveValue(int Index)
{
	if (Index < 0 || Index >= Values.size())
	{
		return;
	}

	Values.erase(Values.begin() + Index);
}

int VarArray::Size() const
{
	return Values.size();
}

int VarArray::PopInt() const
{
	int Ret = 0;
	if (Values.size() > 0)
	{
		VarObject& Var = Values.at(0);
		if (Var.ValueType() == EValueType::Integer)
		{
			Ret = Var.IntVal();
			Values.pop_back();
		}
	}

	return Ret;
}

float VarArray::PopFloat() const
{
	float Ret = 0.f;
	if (Values.size() > 0)
	{
		VarObject& Var = Values.at(0);
		if (Var.ValueType() == EValueType::Float)
		{
			Ret = Var.FloatVal();
			Values.pop_back();
		}
	}
	
	return Ret;
}

FString VarArray::PopString() const
{
	FString Ret("");
	if (Values.size() > 0)
	{
		VarObject& Var = Values.at(0);
		if (Var.ValueType() == EValueType::String)
		{
			Ret = Var.StrVal();
			Values.pop_back();
		}
	}

	return Ret;
}

UObject* VarArray::PopObject() const
{
	UObject* Ret = nullptr;
	if (Values.size() > 0)
	{
		VarObject& Var = Values.at(0);
		if (Var.ValueType() == EValueType::Object)
		{
			Ret = Var.ObjVal();
			Values.pop_back();
		}
	}

	return Ret;
}