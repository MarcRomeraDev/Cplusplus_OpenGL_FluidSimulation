#include "Mesh.h"

Mesh::Mesh() : LStretchX(0.5), LStretchY(0.5), useCollision(0)
{
}

Mesh::Mesh(int _width, int _height, glm::vec3 _initPos, float _LStretchX, float _LStretchY, bool _useCollision) : width(_width), height(_height), initPos(_initPos), LStretchX(_LStretchX), LStretchY(_LStretchY), useCollision(_useCollision), ParticleSystem(_width* _height)
{
	InitMesh();
}

void Mesh::InitMesh()
{
	Wave wave1(0.5, 5, 0.2, glm::vec3(1, 0, 1)); // We set the wave info
	Wave wave2(0.5, 5, 0.2, glm::vec3(1, 0, -1)); // We set the wave info

	waves.push_back(wave1);
	waves.push_back(wave2);
	
	initPos.x = -5;
	for (int row = 0; row < height; row++) // Inicialitzem la Mesh
	{
		for (int col = 0; col < width; col++)
		{
			positions[GetIndex(row, col)] = glm::vec3(initPos.x + (col * LStretchX), initPos.y, initPos.z - (row * LStretchY));
			positionsBefore[GetIndex(row, col)] = positions[GetIndex(row, col)];
		}
	}
}

int Mesh::GetIndex(int _row, int _col) { return _row * width + _col; } // Funció que retorna l'index d'una particula rebent la seva fila i columna

glm::vec3 Mesh::CalculateForce()
{
	return glm::vec3(1);
}

void Mesh::GerstnerWaves(float time) // Calcul de les noves posicions dels vèrtex del "Fluid"
{
	glm::vec3 x; // Nova posicio sobre el pla
	float y;	 // Altura

	for (int row = 0; row < height; row++) 
	{
		for (int col = 0; col < width; col++)
		{
			x = glm::vec3(0);
			y = 0;

			for (int i = 0; i < waves.size(); i++) // Per cada ona, apliquem el sumatori de forçes
			{
				x += (waves[i].direction / waves[i].waveNumber) * waves[i].amplitude 
					* glm::sin(glm::dot(waves[i].direction, positionsBefore[GetIndex(row, col)]) - waves[i].frequency * time); 

				y += waves[i].amplitude * glm::cos(glm::dot(waves[i].direction, positionsBefore[GetIndex(row, col)]) - waves[i].frequency * time);
			}
			// Li apliquem l'offset de la posició inicial a la funció
			x = positionsBefore[GetIndex(row, col)] - x;
			positions[GetIndex(row, col)] = glm::vec3(x.x, positionsBefore[GetIndex(row, col)].y + y, x.z);
		}
	}
}
float Mesh::GetHeightInPos(glm::vec3 sphereCenter, float time){


	int y = 0;
	for (int i = 0; i < waves.size(); i++) // Per cada ona, apliquem el sumatori de forçes
	{
	//	y += waves[i].amplitude * glm::cos(glm::dot(waves[i].direction, liquidPos) - waves[i].frequency * time);
	}
	y += initPos.y;
	return y;
}