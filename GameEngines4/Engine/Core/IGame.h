#ifndef IGAME_H
#define IGAME_H

class IGame {
public:
	// constructor and destructor
	IGame() { }
	virtual ~IGame() { }

	virtual bool OnCreate() = 0;
	virtual void Update(const float& delta) = 0;
	virtual void Render() = 0;
	virtual void Draw() = 0;
	virtual void OnDestroy() = 0;
};

#endif // !IGAME_H