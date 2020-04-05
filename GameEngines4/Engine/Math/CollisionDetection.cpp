#include "CollisionDetection.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

Ray CollisionDetection::ScreenToWorldPosition(vec2 mousePos, vec2 screenSize, Camera* camera) {
	vec4 rayStartNDC((mousePos.x / screenSize.x - 0.5f) * 2.0f, (mousePos.y / screenSize.y - 0.5f) * 2.0f, -1.0f, 1.0f);
	vec4 rayEndNDC((mousePos.x / screenSize.x - 0.5f) * 2.0f, (mousePos.y / screenSize.y - 0.5f) * 2.0f, 0.0f, 1.0f);

	mat4 inverse = glm::inverse(camera->GetPersp() * camera->GetView());

	vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndNDC.w;

	vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayOBBIntersection(Ray* ray, const BoundingBox* box) {
	float tmin = CoreEngine::GetSingleton()->GetCamera()->GetClippingPlanes().x;
	float tmax = CoreEngine::GetSingleton()->GetCamera()->GetClippingPlanes().y;

	vec3 OBBPositionWorld(box->transform[3].x, box->transform[3].y, box->transform[3].z);
	vec3 delta = OBBPositionWorld - ray->position;

	// x axis
	vec3 xAxis(box->transform[0].x, box->transform[0].y, box->transform[0].z);
	float e = glm::dot(xAxis, delta);
	float f = glm::dot(ray->direction, xAxis);
	if (fabs(f) > 0.001f) {
		float t1 = (e + box->min.x) / f;
		float t2 = (e + box->max.x) / f;

		if (t1 > t2) {
			float tmp = t1;
			t1 = t2; t2 = tmp;
		}

		if (t2 < tmax)
			tmax = t2;

		if (t1 > tmin)
			tmin = t1;

		if (tmax < tmin)
			return false;


	} else {
		
		if (-e + box->min.x > 0.0f || -e + box->max.x < 0.0f)
			return false;


	}

	// y axis


	// z axis


	ray->distance = tmin;
	return true;
}
