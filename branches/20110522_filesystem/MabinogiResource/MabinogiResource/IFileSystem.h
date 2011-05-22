#pragma once

class IFolder;
class IFileSystem
{
public:

	IFileSystem(void)
	{
	}

	virtual ~IFileSystem(void)
	{
	}

	virtual IFolder * GetRoot() = 0;


};

