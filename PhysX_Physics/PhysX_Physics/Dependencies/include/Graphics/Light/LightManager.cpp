#include "LightManager.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

LightManager& LightManager::GetInstance()
{
	static LightManager instance;
	return instance;
}

LightManager::Light_NUB::Light_NUB()
{
	position = glm::vec4(0, 0, 0, 1);
	direction = glm::vec4(0, 0, 0, 1);
	baseColor = glm::vec4(1);
	ambientColor = glm::vec4(1);
	atten = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	type_innerAngle_outerAngle_w = glm::vec4(0, 0, 1, 1);
	param2 = glm::vec4(0);
}


void LightManager::Initialize()
{
	for (int i = 0; i < shaders.size(); i++)
	{

		shaders[i]->Bind();

		GLuint lightDataNUB_ID = GL_INVALID_INDEX;
		lightDataNUB_ID = glGetUniformBlockIndex(shaders[i]->shaderId, "lightDataNUB");

		if (lightDataNUB_ID == GL_INVALID_INDEX)
		{
			continue;
		}

		GLCALL(glGenBuffers(1, &lightNubId));
		GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, lightNubId));


		SIZE_OF_LIGHT_NUB = sizeof(Light_NUB) * NUMBER_OF_LIGHTS_IN_USE;

		GLCALL(glBufferData(
			GL_UNIFORM_BUFFER,
			SIZE_OF_LIGHT_NUB,
			NULL,
			GL_DYNAMIC_DRAW));

		GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));

		const GLuint lightDataNUB_ID_binding_Point_number = 0;     // <-- I picked 12 for no reason

		GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, lightDataNUB_ID_binding_Point_number, lightNubId));


		GLCALL(glUniformBlockBinding(shaders[i]->shaderId, lightDataNUB_ID,
			lightDataNUB_ID_binding_Point_number));


		//// Tie the buffer we created to the same binding point
		//// Uniform block binding indices refer to blocks bound to indices in the 
		////  GL_UNIFORM_BUFFER indexed target with glBindBufferRange.
		//GLCALL(glBindBufferRange(GL_UNIFORM_BUFFER,             // Type of buffer
		//	lightDataNUB_ID_binding_Point_number,				// Binding point
		//	lightDataNUB_ID,									// Buffer ID ('name')
		//	0,													// Offset (in bytes)
		//	SIZE_OF_LIGHT_NUB));

		shaders[i]->Unbind();
	}

}

void LightManager::SetLightShader(Shader& lightShader)
{
	this->lightShader = &lightShader;
}

void LightManager::AddLight(Light* light)
{
	if (lights.size() >= NUMBER_OF_LIGHTS_IN_USE)
	{
		Debugger::Print("Number of lights exceeded");
		return;
	}

	switch (light->lightType)
	{
	case Point:
		light->name = "Point Light";
		break;

	case Directional:
		light->name = "Directional Light";
		break;

	case Spot:
		light->name = "Spot Light";
		break;
	}

	lights.push_back(light);
}

void LightManager::AddShader(Shader* shader)
{
	shaders.push_back(shader);
}

void LightManager::RemoveLight(Light* light)
{
	/*if (lights.size() != 0)
	{
		lights.erase(std::remove(lights.begin(), lights.end(), light),lights.end());
	}*/
}

void LightManager::AddLight(Light& light)
{
	if (lights.size() >= NUMBER_OF_LIGHTS_IN_USE)
	{
		Debugger::Print("Number of lights exceeded");
		return;
	}

	lights.push_back(&light);
}

void LightManager::AddShader(Shader& shader)
{
	shaders.push_back(&shader);
}

void LightManager::RemoveLight(Light& light)
{
	/*if (lights.size() != 0)
	{
		lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
	}*/
}

std::vector<Light*> LightManager::GetListOfLights()
{
	return lights;
}

/*
void LightManager::RenderLight()
{
	for (int i = 0; i < shaders.size(); i++)
	{
		shaders[i]->Bind();
		for (int j = 0; j < lights.size(); j++)
		{
			std::string str = std::to_string(j);

			//lightPos
			glm::vec3 value = lights[j]->transform.position;
			shaders[i]->SetUniform4f("lights[" + str + "]." + "position", value.x, value.y, value.z, 1.0f);

			//direction
			value = lights[j]->transform.GetForward();
			shaders[i]->SetUniform4f("lights[" + str + "]." + "direction", value.x, value.y, value.z, 1.0f);

			//baseColor
			glm::vec4 valueVec4 = lights[j]->GetLightColor();
			shaders[i]->SetUniform4f("lights[" + str + "]." + "baseColor", valueVec4.x, valueVec4.y, valueVec4.z, valueVec4.w);

			//ambientColor
			valueVec4 = lights[j]->GetAmbientColor();
			shaders[i]->SetUniform4f("lights[" + str + "]." + "ambientColor", valueVec4.x, valueVec4.y, valueVec4.z, valueVec4.w);

			//atten
			shaders[i]->SetUniform4f("lights[" + str + "]." + "atten",
				lights[j]->attenuation.x,	//Constant
				lights[j]->attenuation.y,	//Linear
				lights[j]->attenuation.z,	//Quadratic
				lights[j]->attenuation.w);	//CutOff

			//type_innerAngle_outerAngle_w
			shaders[i]->SetUniform4f("lights[" + str + "]." + "type_innerAngle_outerAngle_w",
				(int)lights[j]->lightType,	//lightType
				lights[j]->innerAngle,		//InnerAngle
				lights[j]->outerAngle,		//OuterAngle
				0);							//TBD

			//param2
			shaders[i]->SetUniform4f("lights[" + str + "]." + "param2",
				(int)lights[j]->isActive,	//LightActive
				0,							//TBD
				0,							//TBD
				0);							//TBD
		}
		shaders[i]->Unbind();

	}

}
*/
void LightManager::RenderLight()
{
	for (unsigned int index = 0; index != lights.size(); index++)
	{
		lightNubs[index].position = glm::vec4(lights[index]->transform.position, 1.0f);
		lightNubs[index].direction = glm::vec4(lights[index]->transform.GetForward(), 1.0f);
		lightNubs[index].baseColor = lights[index]->GetLightColor();
		lightNubs[index].ambientColor = lights[index]->GetAmbientColor();
		lightNubs[index].atten = lights[index]->attenuation;
		lightNubs[index].type_innerAngle_outerAngle_w = glm::vec4((int)lights[index]->lightType, lights[index]->innerAngle, lights[index]->outerAngle, 0);
		lightNubs[index].param2 = glm::vec4((int)lights[index]->isActive, 0, 0, 0);
	}

	for (int i = 0; i < shaders.size(); i++)
	{
		shaders[i]->Bind();
	
		GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, lightNubId));

		GLCALL(glBufferSubData(GL_UNIFORM_BUFFER,
			0,
			SIZE_OF_LIGHT_NUB,
			&(this->lightNubs)));

		GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));

		shaders[i]->Unbind();
	}
}


void LightManager::Clear()
{
	while (lights.size() != 0)
	{
		delete lights[0];
		lights.erase(lights.begin());
	}

	lights.clear();
}

