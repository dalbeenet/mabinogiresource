#pragma once

#include "ExportMacro.h"

class MABINOGIRESOURCE_API IObject
{
public:

	IObject(void)
	{
	}

	virtual ~IObject(void)
	{
	}

	IObject(IObject const & other) 
	{
		DoCopyConstructor(other);
	}
	IObject& operator=(IObject const & other)
	{
		return DoAssignmentOperation(other);
	}

protected:
	virtual void DoCopyConstructor(IObject const & other) = 0;
	virtual IObject& DoAssignmentOperation(IObject const & other) = 0;
};

