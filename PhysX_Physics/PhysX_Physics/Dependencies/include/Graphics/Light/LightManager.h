#pragma once

#include "../Debugger.h"
#include "Light.h"
#include "../Shaders/Shader.h"

class LightManager
{
public:

	struct Light_NUB
	{
		Light_NUB();
		glm::vec4 position;
		glm::vec4 direction;
		glm::vec4 baseColor;
		glm::vec4 ambientColor;
		glm::vec4 atten;
		glm::vec4 type_innerAngle_outerAngle_w;
		glm::vec4 param2;
	};

	LightManager();
	~LightManager();

	static LightManager& GetInstance();

	void Initialize();

	void SetLightShader(Shader& lightShader);
	void AddLight(Light* light);
	void AddShader(Shader* shader);
	void RemoveLight(Light* light);

	void AddLight(Light& light);
	void AddShader(Shader& shader);
	void RemoveLight(Light& light);
	std::vector<Light*> GetListOfLights();

	void RenderLight();

	void Clear();

private:
	std::vector<Light*> lights;
	std::vector<Shader*> shaders;
	Shader* lightShader = nullptr;

	static const unsigned int NUMBER_OF_LIGHTS_IN_USE = 10;

	unsigned int SIZE_OF_LIGHT_NUB;

	Light_NUB lightNubs[NUMBER_OF_LIGHTS_IN_USE];
	GLuint lightNubId = 0;
};

