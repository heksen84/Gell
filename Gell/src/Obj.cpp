/*
 * Obj.cpp
 *
 *  Created on: 01 ����. 2017 �.
 *      Author: ����
 */

#include "Obj.h"

Obj::Obj() {
}

Obj::~Obj() {
}

void Obj::loadFromFile(const String &filename) {

	msg::info("%s loaded!", filename.c_str());
}

