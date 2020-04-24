#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
//std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();

OctSpatialPartition* CollisionHandler::scenePartition = nullptr;


CollisionHandler::CollisionHandler() {
	//colliders.reserve(10);
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance() {
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}

	return collisionInstance.get();
}

void CollisionHandler::OnDestroy() {
	//for (auto go : colliders) {
	//	go = nullptr;
	//}
	//colliders.clear();

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();

	delete scenePartition;
	scenePartition = nullptr;
}

void CollisionHandler::OnCreate(float worldSize_) {
	prevCollisions.clear();
	//colliders.clear();

	scenePartition = new OctSpatialPartition(worldSize_);

}


void CollisionHandler::AddObject(GameObject* go_) {
	//colliders.push_back(go_);
	scenePartition->AddObject(go_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_) {
	Ray mouseRay = CollisionDetection::ScreenPosToWorldRay(mousePosition_,
		CoreEngine::GetInstance()->GetWindowSize(),
		CoreEngine::GetInstance()->GetCamera());

	//GameObject* hitResult = nullptr;
	//float shortestDist = FLT_MAX;

	//for (auto go : colliders) {
	//	if (mouseRay.IsColliding(&go->GetBoundingBox())) {
	//		if (mouseRay.intersectionDist < shortestDist) {
	//			hitResult = go;
	//			shortestDist = mouseRay.intersectionDist;
	//		}
	//	}
	//}


	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);	
		
		//old code
		if (hitResult) {
		hitResult->SetHit(true, buttonType_);
		}

		for (auto c : prevCollisions) {
			if (c != hitResult && c != nullptr) {
				c->SetHit(false, buttonType_);
				c = nullptr;
			}
		}

		prevCollisions.clear();

		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
		//end of old code
	}





}

