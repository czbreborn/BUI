#ifndef __BUIDEF_H__
#define __BUIDEF_H__

#pragma once

namespace BUI{
	// forbidden copy
	class BUI_API BNoCopy
	{
	public:
		BNoCopy() {};

		virtual void Clone() {};

	private:
		BNoCopy(const BNoCopy& b);
		BNoCopy& operator=(const BNoCopy& b);
	};
}

#endif