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

	// �����ͷŲ���
	virtual void Release() = 0;
};

