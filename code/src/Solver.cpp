#include "Solver.h"

Solver::Solver() : gravity(0, -9.81, 0), useSphereCollision(0) {}
Solver::Solver(glm::vec3 spherePos, float sphereRadius, bool _useSphereCollision) : gravity(0, -9.81, 0), useSphereCollision(_useSphereCollision)
{
	sphere.c = spherePos;
	sphere.r = sphereRadius;
}

//Calcula i retorna la dist�ncia entre un punt i un pl� del cub
float Solver::GetDistanceFromPlane(int plane, glm::vec3 pos)
{
	return (glm::abs((box.norms[plane].x * pos.x) + (box.norms[plane].y * pos.y) + (box.norms[plane].z * pos.z) + box.d[plane])) /
		(glm::sqrt(glm::pow(box.norms[plane].x, 2) + glm::pow(box.norms[plane].y, 2) + glm::pow(box.norms[plane].z, 2)));
}

//Calcula i retorna la normal del pl� a partir del punt de contacte i el centre de l'esfera
glm::vec3 Solver::GetCollisionNorm(glm::vec3 collisionPos, glm::vec3 sphereC)
{
	return glm::normalize(collisionPos - sphereC);
}

//Calcula i retorna la "d" del pl� a partir de la posici� de contacte i la normal
float Solver::GetDFromPlane(glm::vec3 collisionPos, glm::vec3 normal)
{
	return -(collisionPos.x * normal.x) -
		(collisionPos.y * normal.y) -
		(collisionPos.z * normal.z);
}

//Calcula i retorna el punt de contacte de la col�lisi� amb l'esfera a partir de la posici� inicial, l'actual, el centre de l'esfera i el radi
glm::vec3 Solver::GetCollisionPoint(glm::vec3 iPos, glm::vec3 pos, glm::vec3 sphereC, float sphereR)
{
	float a = 0, b = 0, c = 0, delta = 0, lambda = 0;
	glm::vec3 vD = pos - iPos;
	glm::vec3 collisionPos;

	a = glm::pow(vD.x, 2) + glm::pow(vD.y, 2) + glm::pow(vD.z, 2);
	b = 2 * glm::dot(iPos - sphereC, vD);
	c = glm::pow((iPos.x - sphereC.x), 2) + glm::pow((iPos.y - sphereC.y), 2) + glm::pow((iPos.z - sphereC.z), 2) - glm::pow(sphereR, 2);

	delta = glm::pow(b, 2) - (4 * a * c);

	if (delta == 0)
	{
		lambda = -b / (2 * a);
		collisionPos.x = iPos.x + lambda * vD.x;
		collisionPos.y = iPos.y + lambda * vD.y;
		collisionPos.z = iPos.z + lambda * vD.z;
	}
	else if (delta > 0)
	{
		lambda = (-b - glm::sqrt(delta)) / (2 * a);
		collisionPos.x = iPos.x + lambda * vD.x;
		collisionPos.y = iPos.y + lambda * vD.y;
		collisionPos.z = iPos.z + lambda * vD.z;

		if (glm::dot(collisionPos, iPos) < 0)
		{
			lambda = (-b + glm::sqrt(delta)) / (2 * a);
			collisionPos.x = iPos.x + lambda * vD.x;
			collisionPos.y = iPos.y + lambda * vD.y;
			collisionPos.z = iPos.z + lambda * vD.z;
		}
	}

	return collisionPos;
}

//Calcul del rebot en el pl� amb Euler
//void Solver::ReboundPlane(glm::vec3& p, glm::vec3& v, glm::vec3 n, float d)
//{
//	p -= (1 + reboundCoefficient) * (glm::dot(n, p) + d) * n;
//	v -= (1 + reboundCoefficient) * (glm::dot(n, v)) * n;
//
//	//Aix� �s un offset per si hi hagu�s alg�n cas l�mit on alguna part�cula atravessa la col�lisi� de les parets i es quedessin enganxades
//	if (glm::dot(n, p) + d == 0.f) p += n * 0.001f;
//
//	glm::vec3 vN = glm::dot(n, v) * n;
//	glm::vec3 vT = v - vN;
//
//	v = v - frictionCoefficient * vT;
//}

//Calcula la col�lisi� amb una esfera i retorna si s'ha colisionat o no
bool Solver::CheckCollisionSphere(glm::vec3 pos, glm::vec3 sphereCenter, float radius) 
{
	return (glm::abs(glm::distance(sphereCenter, pos)) - radius <= 0);
}