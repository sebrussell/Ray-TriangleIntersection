#include "OBJ_Loader.h"
#include "OpenGL.h"
#include "Math.h"

class Object
{
	public:
		Object(std::string _location);
		~Object();
		void Draw();
		void DrawHit();
	private:
		objl::Loader m_loader;
		int vertexAmount;
		unsigned int VBO, VAO;
		std::vector<Plane> triangles;	
		
		bool CheckForIntersection(Ray _ray);
};