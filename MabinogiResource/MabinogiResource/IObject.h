#pragma once
class IObject
{
public:

	IObject(void)
	{
	}

	virtual ~IObject(void)
	{
	}

	// 进行释放操作
	virtual void Release() = 0;
};

