#include "DrawHelper.h"

std::vector<std::vector<glm::vec3>> DrawHelper::drawFaces(float size, glm::vec3 pos, bool top, bool bottom, bool left, bool right, bool front, bool back)
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
    
    //get the normals of each point
    glm::vec3 frontTopLeftNorm = getNormal(frontTopLeft, backTopLeft, frontTopRight, frontBottomLeft);
    glm::vec3 frontTopRightNorm = getNormal(frontTopRight, frontTopLeft, backTopRight, frontBottomRight);
    glm::vec3 frontBottomLeftNorm = getNormal(frontBottomLeft, frontBottomRight, backBottomLeft, frontTopLeft);
    glm::vec3 frontBottomRightNorm = getNormal(frontBottomRight, backBottomRight, frontBottomLeft, frontTopRight);
    
    glm::vec3 backTopLeftNorm = getNormal(backTopLeft, backTopRight, frontTopLeft, backBottomLeft);
    glm::vec3 backTopRightNorm = getNormal(backTopRight, frontTopRight, backTopLeft, backBottomRight);
    glm::vec3 backBottomLeftNorm = getNormal(backBottomLeft, frontBottomLeft, backBottomRight, backTopLeft);
    glm::vec3 backBottomRightNorm = getNormal(backBottomRight, backBottomLeft, frontBottomRight, backTopRight);

	std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

	//get the points needed to draw the face
	if (top)
	{
		std::vector<std::vector<glm::vec3>> topFace = drawPlane(frontTopLeft, frontTopRight, backTopRight, backTopLeft, frontTopLeftNorm, frontTopRightNorm, backTopRightNorm, backTopLeftNorm);
		vertices.insert(vertices.end(), topFace[0].begin(), topFace[0].end());
        normals.insert(normals.end(), topFace[1].begin(), topFace[1].end());
	}

	if (bottom)
	{
		std::vector<std::vector<glm::vec3>> bottomFace = drawPlane(backBottomLeft, backBottomRight, frontBottomRight, frontBottomLeft, backBottomLeftNorm, backBottomRightNorm, frontBottomRightNorm, frontBottomLeftNorm);
		vertices.insert(vertices.end(), bottomFace[0].begin(), bottomFace[0].end());
        normals.insert(normals.end(), bottomFace[1].begin(), bottomFace[1].end());
	}

	if (left)
	{
		std::vector<std::vector<glm::vec3>> leftFace = drawPlane(frontTopLeft, backTopLeft, backBottomLeft, frontBottomLeft, frontTopLeftNorm, backTopLeftNorm, backBottomLeftNorm, frontBottomLeftNorm);
		vertices.insert(vertices.end(), leftFace[0].begin(), leftFace[0].end());
        normals.insert(normals.end(), leftFace[1].begin(), leftFace[1].end());
	}

	if (right)
	{
		std::vector<std::vector<glm::vec3>> rightFace = drawPlane(backTopRight, frontTopRight, frontBottomRight, backBottomRight, backTopRightNorm, frontTopRightNorm, frontBottomRightNorm, backBottomRightNorm);
		vertices.insert(vertices.end(), rightFace[0].begin(), rightFace[0].end());
        normals.insert(normals.end(), rightFace[1].begin(), rightFace[1].end());
	}

	if (front)
	{
		std::vector<std::vector<glm::vec3>> frontFace = drawPlane(frontTopRight, frontTopLeft, frontBottomLeft, frontBottomRight, frontTopRightNorm, frontTopLeftNorm, frontBottomLeftNorm, frontBottomRightNorm);
		vertices.insert(vertices.end(), frontFace[0].begin(), frontFace[0].end());
        normals.insert(normals.end(), frontFace[1].begin(), frontFace[1].end());
	}

	if (back)
	{
        std::vector<std::vector<glm::vec3>> backFace = drawPlane(backTopLeft, backTopRight, backBottomRight, backBottomLeft, backTopLeftNorm, backTopRightNorm, backBottomRightNorm, backBottomLeftNorm);
		vertices.insert(vertices.end(), backFace[0].begin(), backFace[0].end());
        normals.insert(normals.end(), backFace[1].begin(), backFace[1].end());
	}

    return {vertices, normals};
}

std::vector<std::vector<glm::vec3>> DrawHelper::drawPlane(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomRight, glm::vec3 bottomLeft, glm::vec3 topLeftNorm, glm::vec3 topRightNorm, glm::vec3 bottomRightNorm, glm::vec3 bottomLeftNorm)
{
	std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

	//needs to go counter clockwise
    vertices.push_back(bottomRight);
    vertices.push_back(topRight);
	vertices.push_back(topLeft);
	
    
    vertices.push_back(bottomRight);
    vertices.push_back(topLeft);
	vertices.push_back(bottomLeft);
    
    normals.push_back(bottomRightNorm);
    normals.push_back(topRightNorm);
    normals.push_back(topLeftNorm);
    
    normals.push_back(bottomRightNorm);
    normals.push_back(topLeftNorm);
    normals.push_back(bottomLeftNorm);
    
    return {vertices, normals};
}

glm::vec3 DrawHelper::getPoint(bool isTop, bool isLeft, bool isFront, float size, glm::vec3 pos)
{
	glm::vec3 returnPos = pos;

	returnPos.x += isLeft ? -size : size;
	returnPos.y += isTop ? size : -size;
	returnPos.z += isFront ? -size : size;

	return returnPos;
}

glm::vec3 DrawHelper::getNormal(glm::vec3 target, glm::vec3 right, glm::vec3 left, glm::vec3 down)
{
    glm::vec3 vec1 = right - target;
    glm::vec3 vec2 = left - target;
    glm::vec3 vec3 = down - target;
    
    //now use the combined vectors to get the normals
    glm::vec3 norm1 = glm::cross(vec1, vec2);
    glm::vec3 norm2 = glm::cross(vec2, vec3);
    glm::vec3 norm3 = glm::cross(vec3, vec1);
    
    //return the resulting normal
    return glm::normalize((norm1 + norm2 + norm3) / 3.0f);
}
