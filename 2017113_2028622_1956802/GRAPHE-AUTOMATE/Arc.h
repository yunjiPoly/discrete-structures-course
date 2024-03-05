///////////////////////////////////////////////////////////////////////////////
/// @file graph.cpp
/// @author Yun Ji Liao 2017113
/// @date 2021/06/06
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef __ARC_H
#include <string>

class Arc {
public:
	Arc(int);
	~Arc();
	void setDistance(int distance);
	int getDistance();
private:
	int distance_{ 0 };
};


#endif //  __ARCE_H
