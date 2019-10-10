
#include <iostream>

// glm
#include <glm/gtc/matrix_transform.hpp>

// project
#include "camera.hpp"
#include "opengl.hpp"


using namespace std;
using namespace glm;


void Camera::setPositionOrientation(const vec3 &pos, float yaw, float pitch) {
	m_position = pos;
	m_yaw = yaw;
	m_pitch = pitch;

	// update rotation matrix (based on yaw and pitch)
	m_rotation = rotate(mat4(1), m_yaw, vec3(0, 1, 0)) * rotate(mat4(1), m_pitch, vec3(1, 0, 0));
}


Ray Camera::generateRay(const vec2 &pixel) {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Generate a ray in the scene using the camera position,
	// rotation field of view on the y axis (fovy) and the image
	// size. The pixel is given in image coordinates [0, imagesize]
	// This COULD be done by first creating the ray in ViewSpace
	// then transforming it by the position and rotation to get
	// it into worldspace.
	//-------------------------------------------------------------
	
	Ray ray;

	// YOUR CODE GOES HERE
	// ...
    
	//origin
    ray.origin = m_position;
    
    float NDCX = (pixel.x)/m_image_size.x;
    float NDCY = (pixel.y)/m_image_size.y;
    
    float screenX = (2*NDCX)-1;
    float screenY = (2*NDCY)-1;
    
    float imgRatio = m_image_size.x/m_image_size.y;
    
    //float camX = ((2*screenX)-1)*imgRatio;
    //float camY = (1-(2*screenY));
    
    float fovX = screenX*imgRatio*tan(m_fovy/2);
    float fovY = screenY*tan(m_fovy/2);
    
    
    
    vec3 camSpace = vec4(glm::normalize(glm::vec3(fovX, fovY, -1) - m_position), 0)*m_rotation;
    
    ray.direction = vec3(camSpace.x, camSpace.y, camSpace.z);
    
	return ray;
}

//for(int x = 0; x<m_image_size.x; x++){
//    for(int y = 0; y<m_image_size.y; y++){
//        float tNear = INFINITY;
//        objNear = null;
//
//
//    }
//    }
