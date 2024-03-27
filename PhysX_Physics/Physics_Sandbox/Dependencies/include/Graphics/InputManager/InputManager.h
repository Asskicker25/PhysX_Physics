#pragma once

#include "iInputListener.h"
#include <vector>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class InputManager
{
private:
	std::vector<iInputListener*> inputListeners;

	class Pimpl;
	Pimpl* pimpl;

	float mAxisX = 0;
	float mAxisY = 0;
	float mSmoothMouseInputX = 0;
	float mSmoothMouseInputY = 0;


	bool mLeftHeld = false;
	bool mRightHeld = false;
	bool mUpHeld = false;
	bool mDownHeld = false;

	void CalculateAxis();

public:
	InputManager();
	~InputManager();

	static InputManager& GetInstance();

	void AddListener(iInputListener* inputListener);
	void RemoveListener(iInputListener* inputListener);

	void OnKeyPressed(const int& key);
	void OnKeyReleased(const int& key);
	void OnKeyHeld();

	void OnMouseButtonPressed(const int& key);
	void OnMouseButtonReleased(const int& key);

	void SetMouseInput(float smoothInputX, float smoothInputY);

	float GetMouseAxisX();
	float GetMouseAxisY();
	float GetAxisX();
	float GetAxisY();

	void Update();
	void Clear();

	glm::vec2 mMouseDelta = glm::vec2(0);
	glm::vec2 mCurrentMousePos = glm::vec2(0);
	glm::vec2 mLastMousePos = glm::vec2(0);


};

