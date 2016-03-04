#pragma once

// forbidden copy
class BUI_API BNoCopy
{
public:
	BNoCopy() {};

private:
	BNoCopy(const BNoCopy& b);
	BNoCopy& operator=(const BNoCopy& b);
};