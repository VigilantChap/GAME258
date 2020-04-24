#include "OctSpatialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 position_, float size_, OctNode* parent_) 
	: parent(nullptr), octBounds(nullptr), objectList(std::vector<GameObject*>()), children()
{
	objectList.reserve(10);
	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;
	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		children[i] = nullptr;
	}
}

OctNode::~OctNode() {
	OnDestroy();
}

void OctNode::OnDestroy() {
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) {
		for (auto obj : objectList) {
			obj = nullptr;
		}
		objectList.clear();
	}

	parent = nullptr;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		if (children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth_) {
	if (depth_ > 0 && this) {
		float half = size / 2.0f;
		children[static_cast<int>(OctChildren::OCT_TLF)] =
			new OctNode(glm::vec3(octBounds->minVert.x, 
				octBounds->minVert.y + half, 
				octBounds->minVert.z + half), 
				half, this);

		children[static_cast<int>(OctChildren::OCT_BLF)] =
			new OctNode(glm::vec3(octBounds->minVert.x,
				octBounds->minVert.y,
				octBounds->minVert.z + half),
				half, this); 

		children[static_cast<int>(OctChildren::OCT_BRF)] =
			new OctNode(glm::vec3(octBounds->minVert.x + half,
				octBounds->minVert.y,
				octBounds->minVert.z + half),
				half, this);

		children[static_cast<int>(OctChildren::OCT_TRF)] =
			new OctNode(glm::vec3(octBounds->minVert.x + half,
				octBounds->minVert.y + half,
				octBounds->minVert.z + half),
				half, this);

		children[static_cast<int>(OctChildren::OCT_TLR)] =
			new OctNode(glm::vec3(octBounds->minVert.x,
				octBounds->minVert.y + half,
				octBounds->minVert.z),
				half, this);

		children[static_cast<int>(OctChildren::OCT_BLR)] =
			new OctNode(glm::vec3(octBounds->minVert.x,
				octBounds->minVert.y,
				octBounds->minVert.z),
				half, this);

		children[static_cast<int>(OctChildren::OCT_BRR)] =
			new OctNode(glm::vec3(octBounds->minVert.x + half,
				octBounds->minVert.y,
				octBounds->minVert.z),
				half, this);

		children[static_cast<int>(OctChildren::OCT_TRR)] =
			new OctNode(glm::vec3(octBounds->minVert.x + half,
				octBounds->minVert.y + half,
				octBounds->minVert.z),
				half, this);

		childNum += 8;
	}

	if (depth_ > 0 && this) {
		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			children[i]->Octify(depth_ - 1);
		}
	}
}

OctNode* OctNode::GetParent() {
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPosition_) {
	return children[static_cast<int>(childPosition_)];
}

void OctNode::AddCollisionObject(GameObject* obj_) {
	objectList.push_back(obj_);
}

int OctNode::GetObjCount() const {
	return objectList.size();
}

bool OctNode::IsLeaf() const {
	if (children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const {
	return octBounds;
}

int OctNode::GetChildCount() const {
	return childNum;
}


//-----------------------------------------------------------------------

OctSpatialPartition::OctSpatialPartition(float worldSize_) {
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " total child nodes." << std::endl;
	rayIntersectionList = std::vector<OctNode*>();
}

OctSpatialPartition::~OctSpatialPartition() {
	OnDestroy();
}

void OctSpatialPartition::OnDestroy() {
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}

		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}

void OctSpatialPartition::AddObject(GameObject* obj_) {
	AddObjectToCell(root, obj_);
}

GameObject* OctSpatialPartition::GetCollision(Ray ray_) {
	for (auto cell : rayIntersectionList) {
		cell = nullptr;
	}
	rayIntersectionList.clear();

	rayIntersectionList.reserve(20);
	PrepareCollisionQuery(root, ray_);

	GameObject* result = nullptr;
	float shortestDistance = FLT_MAX;
	for (auto cell : rayIntersectionList) {
		for (auto obj : cell->objectList) {
			if (ray_.IsColliding(&obj->GetBoundingBox())) {
				if (ray_.intersectionDist < shortestDistance) {
					result = obj;
					shortestDistance = ray_.intersectionDist;
				}
			}
		}
		if (result != nullptr) {
			return result;
		}
	}

	return nullptr;
}

void OctSpatialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_) {
	
	if (cell_->GetBoundingBox()->Intersects(&obj_->GetBoundingBox())) {
		if (cell_->IsLeaf()) {
			cell_->AddCollisionObject(obj_);
		}

		else {
			for (auto child : cell_->children) {
				AddObjectToCell(child, obj_);
			}
		}
	}

}

void OctSpatialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_) {
	if (ray_.IsColliding(cell_->GetBoundingBox())) {
		if (cell_->IsLeaf()) {
			rayIntersectionList.push_back(cell_);
		}

		else {
			for (auto child : cell_->children) {
				PrepareCollisionQuery(child, ray_);
			}
		}
	}
}