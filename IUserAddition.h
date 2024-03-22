#pragma once

class IUserAddition // Base Interface
{
public:
	virtual void AddUser() = 0;
	virtual ~IUserAddition() = default;
};
