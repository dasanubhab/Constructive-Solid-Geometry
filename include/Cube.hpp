#include "VertexBufferLayout.hpp"
#include "Geometry.hpp"
#include <cmath>

class Cube : public Object{
public:
    Cube();
    void Init();
};

// Calls the initalization routine
Cube::Cube(){
    Init();
}

void Cube::Init(){
    // makes basic 2*2*2 cube at origin using data from cube.obj
        m_geometry.AddVertex(-1.0f, -1.0f, -1.0f);
        m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
        m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
        m_geometry.AddVertex(-1.0f, 1.0f, 1.0f);
        m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
        m_geometry.AddVertex(1.0f, -1.0f, 1.0f);
        m_geometry.AddVertex(1.0f, 1.0f, -1.0f);
        m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
        m_geometry.AddIndex(0);
        m_geometry.AddIndex(4);
        m_geometry.AddIndex(1);
        m_geometry.AddIndex(1);
        m_geometry.AddIndex(2);
        m_geometry.AddIndex(0);
        m_geometry.AddIndex(1);
        m_geometry.AddIndex(4);
        m_geometry.AddIndex(5);
        m_geometry.AddIndex(1);
        m_geometry.AddIndex(7);
        m_geometry.AddIndex(3);
        m_geometry.AddIndex(2);
        m_geometry.AddIndex(4);
        m_geometry.AddIndex(0);
        m_geometry.AddIndex(2);
        m_geometry.AddIndex(7);
        m_geometry.AddIndex(6);
        m_geometry.AddIndex(3);
        m_geometry.AddIndex(2);
        m_geometry.AddIndex(1);
        m_geometry.AddIndex(3);
        m_geometry.AddIndex(7);
        m_geometry.AddIndex(2);
        m_geometry.AddIndex(4);
        m_geometry.AddIndex(7);
        m_geometry.AddIndex(5);
        m_geometry.AddIndex(5);
        m_geometry.AddIndex(7);
        m_geometry.AddIndex(1);
        m_geometry.AddIndex(6);
        m_geometry.AddIndex(4);
        m_geometry.AddIndex(2);
        m_geometry.AddIndex(6);
        m_geometry.AddIndex(7);
        m_geometry.AddIndex(4);
        m_geometry.Gen();
        m_vertexBufferLayout.CreatePositionBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());
}