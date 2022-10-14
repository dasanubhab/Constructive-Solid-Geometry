#include "SceneNode.hpp"

#include <string>
#include <iostream>

// The constructor
SceneNode::SceneNode(Object* ob){
	std::cout << "(SceneNode.cpp) Constructor called\n";
	m_object = ob;
	// By default, we do not know the parent
	// at the time of construction of this node.
	// If the SceneNode is the root of the tree,
	// then there is no parent.
	m_parent = nullptr;
	
	// Setup shaders for the node.
	vertexShader = m_shader.LoadShader("./shaders/vert.glsl");
	fragmentShader = m_shader.LoadShader("./shaders/frag.glsl");
	m_shader.CreateShader(vertexShader,fragmentShader);
	vertexShader = m_shader_trans.LoadShader("./shaders/vert.glsl");
	transShader = m_shader_trans.LoadShader("./shaders/fragTransparent.glsl");
	m_shader_trans.CreateShader(vertexShader,transShader);  
	operation = "add";    
	iterations = 1;
}

// The destructor 
SceneNode::~SceneNode(){
	// Remove each object
	for(unsigned int i =0; i < m_children.size(); ++i){
		delete m_children[i];
	}
}

// Adds a child node to our current node.
void SceneNode::AddChild(SceneNode* n){
	// For the node we have added, we can set
	// it's parent now to our current node.
	// 'this' is the current instance of our
	// object, which is a pointer to our current
	// SceneNode.
	n->m_parent = this;
	// Add a child node into our SceneNode
	m_children.push_back(n);
}

// Draw simply draws the current nodes
// object and all of its children. This is done by calling directly
// the objects draw method.
void SceneNode::Draw(){
	// Bind the shader for this node or series of nodes
	// Render our object
	//Use appropriate shader depending on if first or second time
	if(iterations == 2) {
		m_shader.Bind();
	} else {
		m_shader_trans.Bind();
		}
	if(m_object!=nullptr){
		// Use correct stencil function depending on operation and iteration
		if (operation == "add" && iterations == 1) {
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
		} else if (iterations == 1){
			glStencilFunc(GL_ALWAYS, 0, 0xFF);
		} else if (operation == "add"  && iterations == 2) {
			glStencilFunc(GL_EQUAL, 1, 0xFF);
		} else {
			glStencilFunc(GL_NEVER, 0, 0xFF);
		}
		if(iterations == 2) {
			iterations = 0;
		}
		iterations++;
		m_object->Render();
		// For any 'child nodes' also call the drawing routine.
		for(int i =0; i < m_children.size(); ++i){
			m_children[i]->Draw();
		}
	}	
}

// Update simply updates the current nodes
// object. This is done by calling directly
// the objects update method.
// TODO: Consider not passting projection and camera here
void SceneNode::Update(glm::mat4 projectionMatrix, Camera* camera){
    if(m_object!=nullptr){
        // TODO: Implement here!
		this->GetWorldTransform()*=(this->GetLocalTransform());
		for(int i =0; i < m_children.size(); ++i){
			m_children[i]->GetWorldTransform().LoadIdentity();
			m_children[i]->GetWorldTransform().ApplyTransform(this->GetWorldTransform());
		}
		m_shader.Bind();
        m_shader.SetUniform1i("u_DiffuseMap",0);  
        m_shader.SetUniformMatrix4fv("model", &m_worldTransform.GetInternalMatrix()[0][0]);
        m_shader.SetUniformMatrix4fv("view", &camera->GetWorldToViewmatrix()[0][0]);
        m_shader.SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);
        m_shader.SetUniform3f("lightColor",1.0f,1.0f,1.0f);
        m_shader.SetUniform3f("lightPos",
                               camera->GetEyeXPosition() + camera->GetViewXDirection(),
                               camera->GetEyeYPosition() + camera->GetViewYDirection(),
                               camera->GetEyeZPosition() + camera->GetViewZDirection());
        m_shader.SetUniform1f("ambientIntensity",0.5f);
		m_shader_trans.Bind();
        m_shader_trans.SetUniform1i("u_DiffuseMap",0);  
        m_shader_trans.SetUniformMatrix4fv("model", &m_worldTransform.GetInternalMatrix()[0][0]);
        m_shader_trans.SetUniformMatrix4fv("view", &camera->GetWorldToViewmatrix()[0][0]);
        m_shader_trans.SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);
        m_shader_trans.SetUniform3f("lightColor",1.0f,1.0f,1.0f);
        m_shader_trans.SetUniform3f("lightPos",
                               camera->GetEyeXPosition() + camera->GetViewXDirection(),
                               camera->GetEyeYPosition() + camera->GetViewYDirection(),
                               camera->GetEyeZPosition() + camera->GetViewZDirection());
        m_shader_trans.SetUniform1f("ambientIntensity",0.5f);
	
		// Iterate through all of the children
		for(int i =0; i < m_children.size(); ++i){
			m_children[i]->Update(projectionMatrix, camera);
		}
	}
}

void SceneNode::setOp(std::string work){
	operation = work;
}

// Returns the actual local transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::GetLocalTransform(){
    return m_localTransform; 
}

// Returns the worled  transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::GetWorldTransform(){
    return m_worldTransform; 
}
