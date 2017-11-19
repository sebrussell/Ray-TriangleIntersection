#include "OBJ_Loader.h"
#include "OpenGL.h"
#include "Math.h"

class Object
{
	public:
		Object(std::string _location);
		~Object();
		void Draw();
		void DrawHit(int _memoryLocation, bool _hit);
		int CheckForIntersection(Ray _ray);
		int CheckForIntersection();
	private:
		objl::Loader m_loader;
		int vertexAmount;
		unsigned int VBO, VAO;
		std::vector<Plane> triangles;
		std::shared_ptr<Vector3> intersectionPoint;
};