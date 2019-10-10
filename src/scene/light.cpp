
// glm
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

// project
#include "light.hpp"
#include <iostream>
using namespace std;

using namespace glm;


bool DirectionalLight::occluded(Scene *scene, const vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Determine whether the given point is being occluded from
	// this directional light by an object in the scene.
	// Remember that directional lights are "infinitely" far away
	// so any object in the way would cause an occlusion.
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    Ray ray;
    //ray.origin = vec3(INFINITY);
    //ray.direction = point-m_direction;
    
    Ray r = Ray(point-(m_direction*0.01f), -m_direction);
    
    return scene->intersect(r).m_valid;
}


vec3 DirectionalLight::incidentDirection(const vec3 &) const {
	return m_direction;
}


vec3 DirectionalLight::irradiance(const vec3 &) const {
	return m_irradiance;
}


bool PointLight::occluded(Scene *scene, const vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Determine whether the given point is being occluded from
	// this directional light by an object in the scene.
	// Remember that point lights are somewhere in the scene and
	// an occulsion has to occur somewhere between the light and 
	// the given point.
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    
    vec3 dir = point - m_position;
    float length = dir.length();
    Ray ray = Ray(point, normalize(-dir));
    if(length>0){
        if(scene->intersect(ray).m_valid && scene->intersect(ray).m_distance < distance(m_position, point)){
            return true;
        }
    }
	return false;
}


vec3 PointLight::incidentDirection(const vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Return the direction of the incoming light (light to point)
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    
    //vec3 dir(1,0,0);
    vec3 dir = point - m_position;
    float length = dir.length();
    if(length>0){
        return normalize(dir);
    }
    return vec3(0);
}


vec3 PointLight::irradiance(const vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Return the total irradiance on the given point.
	// This requires you to convert the flux of the light into
	// irradiance by dividing it by the surface of the sphere
	// it illuminates. Remember that the surface area increases
	// as the sphere gets bigger, ie. the point is further away.
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    
    //return vec3(1,0,0);
    //return m_flux;
    vec3 dir = point - m_position;
    float length = dir.length();
    
    //float distance = sqrt(length);
   // dir.x /= distance; dir.y /= distance, dir.z /= distance;
    if(length>0){
        float a = 4.0f*M_PI*(length*length);
        //cout<<"return if"<<endl;
        return m_flux/a;
    }
	return m_flux;
}
