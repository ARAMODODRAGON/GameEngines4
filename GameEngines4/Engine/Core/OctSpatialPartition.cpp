#include "OctSpatialPartition.h"


#pragma region OctNode Class

int OctNode::childNum = 0;

OctNode::OctNode(vec3 position, float size_, OctNode* parent)
	: bounds(nullptr), parent(parent), children(), objects(), size(size_) {
	// reserve some memory
	objects.reserve(10);

	bounds = new BoundingBox();
	bounds->min = position;
	bounds->max = position + vec3(size);

	for (size_t i = 0; i < OCT_CHILD_COUNT; ++i)
		children[i] = nullptr;


}

OctNode::~OctNode() {
	OnDestroy();
}

void OctNode::OnDestroy() {
	delete bounds; bounds = nullptr;

	if (objects.size() > 0) {
		for (auto go : objects)
			go = nullptr;
		objects.clear();
	}

	for (size_t i = 0; i < OCT_CHILD_COUNT; ++i) {
		if (children[i]) delete children[i];
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth) {
	if (depth <= 0 || this == nullptr) return;

	float half = size / 2.0f;

	/// top
	children[TO_INT(OctPos::OCTPOS_TLF)] = new OctNode(vec3(bounds->min.x, bounds->min.y + half, bounds->min.z + half), half, this);
	children[TO_INT(OctPos::OCTPOS_TRF)] = new OctNode(vec3(bounds->min.x + half, bounds->min.y + half, bounds->min.z + half), half, this);
	children[TO_INT(OctPos::OCTPOS_TLR)] = new OctNode(vec3(bounds->min.x, bounds->min.y + half, bounds->min.z), half, this);
	children[TO_INT(OctPos::OCTPOS_TRR)] = new OctNode(vec3(bounds->min.x + half, bounds->min.y + half, bounds->min.z), half, this);

	/// bottom
	children[TO_INT(OctPos::OCTPOS_BLF)] = new OctNode(vec3(bounds->min.x, bounds->min.y, bounds->min.z + half), half, this);
	children[TO_INT(OctPos::OCTPOS_BRF)] = new OctNode(vec3(bounds->min.x + half, bounds->min.y, bounds->min.z + half), half, this);
	children[TO_INT(OctPos::OCTPOS_BLR)] = new OctNode(vec3(bounds->min.x, bounds->min.y, bounds->min.z), half, this);
	children[TO_INT(OctPos::OCTPOS_BRR)] = new OctNode(vec3(bounds->min.x + half, bounds->min.y, bounds->min.z), half, this);

	childNum += 8;

	for (size_t i = 0; i < OCT_CHILD_COUNT; ++i)
		children[i]->Octify(depth - 1);


}

void OctNode::AddCollisionObject(GameObject* go) {
	objects.push_back(go);
}

bool OctNode::IsLeaf() const {
	if (children[0] == nullptr) return true;
	return false;
}

#pragma endregion

#pragma region OctSpatialPartition Class

void OctSpatialPartition::PrepareCollisionQuery(OctNode* cell, Ray ray) {
	for (OctNode* child : cell->children) {
		if (ray.OBBCollision(*child->bounds)) {
			// add the cell to the list if it has objects
			if (child->GetObjectCount() > 0)
				rayIntersectionList.push_back(child);

			// recurse for every child
			if (!child->IsLeaf())
				PrepareCollisionQuery(child, ray);
		}
	}
}

OctSpatialPartition::OctSpatialPartition(float worldsize)
	: root(nullptr), rayIntersectionList() {
	// create tree
	root = new OctNode(vec3(-worldsize * 0.5f), worldsize, nullptr);
	root->Octify(3);
	std::cout << "there are " << root->GetChildCount() << " child nodes" << std::endl;

	rayIntersectionList.reserve(20);
}

OctSpatialPartition::~OctSpatialPartition() {
	OnDestroy();
}

void OctSpatialPartition::OnDestroy() {
	delete root; root = nullptr;

	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList)
			cell = nullptr;
		rayIntersectionList.clear();
	}
}

void OctSpatialPartition::AddObject(GameObject* go, OctNode* cell) {
	if (cell->IsLeaf()) {
		cell->objects.push_back(go);
	} else {
		for (OctNode* child : cell->children) {
			if (go->GetBoundingBox().Intersects(child->bounds)) {
				AddObject(go, child);
			}
		}
	}
}

void OctSpatialPartition::AddObject(GameObject* go) {
	AddObject(go, root);
}

GameObject* OctSpatialPartition::GetCollision(Ray ray) {
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}
	PrepareCollisionQuery(root, ray);

	GameObject* result = nullptr;
	float shortestDist = FLT_MAX;
	for (auto cell : rayIntersectionList) {
		for (auto go : cell->objects) {
			if (ray.OBBCollision(go->GetBoundingBox())) {
				if (ray.distance < shortestDist) {
					shortestDist = ray.distance;
					result = go;
				}
			}
		}

		//if (result) break;
	}

	return result;
}

#pragma endregion