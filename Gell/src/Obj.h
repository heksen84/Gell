/*
 * Obj.h
 *
 *  Created on: 01 ����. 2017 �.
 *      Author: ����
 */

#ifndef OBJ_H_
#define OBJ_H_
#include "common.h"

class Obj {
public:
	Obj();
	virtual ~Obj();
	void loadFromFile(const String &filename);
};

#endif /* OBJ_H_ */
