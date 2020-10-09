#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H
#include "GUIComponent.h"
#include <vector>
#include "../Camera/Camera.h"
#include <string>
using std::string;
#include "../Core/Debug.h"

class GUIObject {

	vec2 position;

	std::vector<GUIComponent*> components;

	string tag;

public:

	GUIObject(const vec2& position_);
	~GUIObject();

	void Draw(Camera* camera);

	bool ContainsPoint(const vec2& point);

	// getters & setters
	string GetTag() const { return tag; }
	void SetTag(const string& tag_) { tag = tag_; }

	template<class T>
	T* AddComponent() {
		if (T* t = GetComponent<T>())
			return t;

		T* t = new T();

		if (GUIComponent* c = dynamic_cast<GUIComponent*>(t)) {
			components.push_back(c);
			return t;
		} else {
			delete c;
			DEBUG_ERROR("Cant make GUI component of type");
			return nullptr;
		}
	}

	template<class T>
	T* GetComponent() {
		for (GUIComponent* c : components) {
			if (T* t = dynamic_cast<T*>(c)) {
				return t;
			}
		}
		return nullptr;
	}

	template<class T>
	bool DestroyComponent() {
		for (auto it = components.begin(); it != components.end(); ++it) {
			if (T* t = dynamic_cast<T*>(*it)) {
				delete t;
				components.erase(it);
				return true;
			}
		}
		return false;
	}

};

#endif // !GUI_OBJECT_H