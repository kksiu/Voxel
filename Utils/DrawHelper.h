#pragma once

#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

//class will help draw the planes needed
class DrawHelper {
public:
	//this will draw only certain faces of a square based on what was sent in
	//will return a vector of glm::vec3 since they will be used to create the triangle
	static std::vector<glm::vec3> drawFaces(float size, glm::vec3 pos, 
					bool top = true, bool bottom = true, bool left = true, bool right = true, bool front = true, bool back = true);

	//this will draw a plane based on four points
	//return a set of vectors that can be then put in a vertex buffer
	static std::vector<glm::vec3> drawPlane(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomRight, glm::vec3 bottomLeft);

	//returns a point based on where one needs it to be
	static glm::vec3 getPoint(bool isTop, bool isLeft, bool isFront, float size, glm::vec3 pos);
};