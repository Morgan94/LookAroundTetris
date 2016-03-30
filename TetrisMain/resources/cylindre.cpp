void makeCylinder(Mesh* mesh, float R, float h, Uint32 nbSegR, Uint32 nbSegH, Vec4f color, Bool invertFaces)
{
	mesh->vertices.clear();
	mesh->triangles.clear();

	float theta;
	float currh;
	float X, Y, Z;

	// vertices
	for(Uint32 i=0; i<=nbSegH; i++)
	{
		currh = h * (float)(i) / (float)(nbSegR);
		for(Uint32 j=0; j<nbSegR; j++)
		{
			theta = 2 * PI * (float)(j) / (float)(nbSegH);
			X = R * cos(theta);
			Y = currh;
			Z = R * sin(theta);
			mesh->vertices.push_back(Vertex(Vec3f(X, Y, Z), Vec3f(), Vec3f(), Vec2f(), color));
		}
	}
	
	// indexes
	for(Uint32 v=0; v<mesh->vertices.size(); v++)
	{
		if(invertFaces)
		{
			mesh->triangles.push_back(Triangle(v + nbSegR - 1, v + nbSegR, v));
			mesh->triangles.push_back(Triangle(v + nbSegR, v + 1, v));
		}
		else
		{
			mesh->triangles.push_back(Triangle(v, v + nbSegR, v + nbSegR - 1));
			mesh->triangles.push_back(Triangle(v, v + 1, v + nbSegR));
		}
	}
	
	return;
}