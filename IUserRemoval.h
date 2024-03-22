#pragma once

class IUserRemoval
{
public:
	virtual void RemoveUser() = 0;
	virtual ~IUserRemoval() = default;
};
