/*
 * Obj.cpp
 *
 *  Created on: 01 ����. 2017 �.
 *      Author: ����
 */

#include "Obj.h"

std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec3 > temp_uvs;
std::vector< glm::vec3 > temp_normals;

Obj::Obj() {
}

Obj::~Obj() {
}

/*
 * �������� ������
 */
void Obj::loadFromFile(const String &filename) {
	msg::info("%s loaded", filename.c_str());
}

