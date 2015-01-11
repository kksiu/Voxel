#include "DrawHelper.h"

std::vector<glm::vec3> DrawHelper::drawFaces(float size, glm::vec3 pos, bool top, bool bottom, bool left, bool right, bool front, bool back)
{
	//get the 8 points of a square drawn at the current position
	glm::vec3 frontTopLeft = getPoint(true, true, true, size, pos);
	glm::vec3 frontTopRight = getPoint(true, false, true, size, pos);
	glm::vec3 frontBottomLeft = getPoint(false, true, true, size, pos);
	glm::vec3 frontBottomRight = getPoint(false, false, true, size, pos);

	glm::vec3 backTopLeft = getPoint(true, true, false, size, pos);
	glm::vec3 backTopRight = getPoint(true, false, false, size, pos);
	glm::vec3 backBottomLeft = getPoint(false, true, false, size, pos);
	glm::vec3 backBottomRight = getPoint(false, false, false, size, pos);

	std::vector<glm::vec3> vectorToReturn;

	//get the points needed to draw the face
	if (top)
	{
		std::vector<glm::vec3> topFace = drawPlane(frontTopLeft, frontTopRight, backTopRight, backTopLeft);
		vectorToReturn.insert(vectorToReturn.end(), topFace.begin(), topFace.end());
	}

	if (bottom)
	{
		std::vector<glm::vec3> bottomFace = drawPlane(backBottomLeft, backBottomRight, frontBottomRight, frontBottomLeft);
		vectorToReturn.insert(vectorToReturn.end(), bottomFace.begin(), bottomFace.end());
	}

	if (left)
	{
		std::vector<glm::vec3> leftFace = drawPlane(frontTopLeft, backTopLeft, backBottomLeft, frontBottomLeft);
		vectorToReturn.insert(vectorToReturn.end(), leftFace.begin(), leftFace.end());
	}

	if (right)
	{
		std::vector<glm::vec3> rightFace = drawPlane(backTopRight, frontTopRight, frontBottomRight, backBottomRight);
		vectorToReturn.insert(vectorToReturn.end(), rightFace.begin(), rightFace.end());
	}

	if (front)
	{
		std::vector<glm::vec3> frontFace = drawPlane(frontTopRight, frontTopLeft, frontBottomLeft, frontBottomRight);
		vectorToReturn.insert(vectorToReturn.end(), frontFace.begin(), frontFace.end());
	}

	if (back)
	{
		std::vector<glm::vec3> backFace = drawPlane(backTopLeft, backTopRight, backBottomRight, backBottomLeft);
		vectorToReturn.insert(vectorToReturn.end(), backFace.begin(), backFace.end());
	}

	return vectorToReturn;
}

std::vector<glm::vec3> DrawHelper::drawPlane(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomRight, glm::vec3 bottomLeft)
{
	std::vector<glm::vec3> vectorToReturn;

	//needs to go counter clockwise
	vectorToReturn.push_back(bottomRight);
	vectorToReturn.push_back(topRight);
	vectorToReturn.push_back(topLeft);
	
	vectorToReturn.push_back(bottomRight);
	vectorToReturn.push_back(topLeft);
	vectorToReturn.push_back(bottomLeft);

	return vectorToReturn;
}

glm::vec3 DrawHelper::getPoint(bool isTop, bool isLeft, bool isFront, float size, glm::vec3 pos)
{
	glm::vec3 returnPos = pos;

	returnPos.x += isLeft ? size : -size;
	returnPos.y += isTop ? size : -size;
	returnPos.z += isFront ? -size : size;

	return returnPos;
}