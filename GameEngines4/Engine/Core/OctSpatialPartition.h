#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

#define OCT_CHILD_COUNT 8
#define TO_INT(e) static_cast<int>(e)

enum class OctPos : unsigned char {
	OCTPOS_TLF = 0,
	OCTPOS_BLF = 1,
	OCTPOS_BRF = 2,
	OCTPOS_TRF = 3,
	OCTPOS_TLR = 4,
	OCTPOS_BLR = 5,
	OCTPOS_BRR = 6,
	OCTPOS_TRR = 7
};

class OctNode {
	friend class OctSpatialPartition;

	BoundingBox* bounds;
	OctNode* parent;
	OctNode* children[OCT_CHILD_COUNT];
	std::vector<GameObject*> objects;
	float size;
	static int childNum;

public:


	OctNode(vec3 position, float size, OctNode* parent);
	~OctNode();

	void OnDestroy();
	void Octify(int depth);

	OctNode* GetParent() const { return parent; }
	OctNode* GetChild(OctPos pos) { children[TO_INT(pos)]; }
	void AddCollisionObject(GameObject* go);
	int GetObjectCount() const { return objects.size(); }
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const { return bounds; }
	static int GetChildCount() { return childNum; }

};

class OctSpatialPartition {

	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObject(GameObject* go, OctNode* cell);
	void PrepareCollisionQuery(OctNode* cell, Ray ray);

public:

	OctSpatialPartition(float worldsize);
	~OctSpatialPartition();
	void OnDestroy();
	void AddObject(GameObject* go);
	GameObject* GetCollision(Ray ray);

};

#endif // !OCTSPATIALPARTITION_H