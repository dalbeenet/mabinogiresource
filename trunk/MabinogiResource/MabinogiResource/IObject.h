#pragma once

#include "MabinogiResource.h"

class MABINOGIRESOURCE_API IObject
{
public:

	IObject(void)
	{
	}

	virtual ~IObject(void)
	{
	}

	// �����ͷŲ���
	virtual void Release() = 0;

private:
	IObject(IObject const & other);
	IObject& operator=(IObject const & other);
};

