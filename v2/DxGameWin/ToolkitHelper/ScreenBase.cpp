#include "pch.h"

#include "ScreenBase.h"


using namespace std;
using namespace DX;
using namespace ToolkitHelper;

ScreenBase::ScreenBase(const shared_ptr<DeviceResources>& deviceResources)
	:m_deviceResources(deviceResources){
	
}

void ScreenBase::CreateResources(){
	for (unsigned int i = 0; i < m_renderObjects.size(); i++){
		m_renderObjects.at(i)->CreateResources();
	}
}

void ScreenBase::WindowSizeChanged(){
	for (unsigned int i = 0; i < m_renderObjects.size(); i++){
		m_renderObjects.at(i)->WindowSizeChanged();
	}
}


void ScreenBase::ReleaseResources(){
	for (unsigned int i = 0; i < m_renderObjects.size(); i++){
		m_renderObjects.at(i)->ReleaseResources();
	}
	m_renderObjects.clear();
}

ScreenBase* ScreenBase::Update(const StepTimer& timer,const GameInput& input){
	for (unsigned int i = 0; i < m_renderObjects.size(); i++){
		m_renderObjects.at(i)->Update(timer,input);
	}

	return this;
}

void ScreenBase::Render(){
	for (unsigned int i = 0; i < m_renderObjects.size(); i++){
		m_renderObjects.at(i)->Render();
	}
}

void ScreenBase::AddObject(shared_ptr<GameObject> obj){
	obj->CreateResources();
	m_renderObjects.push_back(obj);
}


bool ScreenBase::RemoveObject(shared_ptr<GameObject> obj){
	int i = 0;
	for (vector<shared_ptr<GameObject>>::iterator ite = m_renderObjects.begin(); ite < m_renderObjects.end(); ite++){
		if (m_renderObjects.at(i) == obj){
			m_renderObjects.erase(ite);
			
			return true;
		}

		i++;
	}
	return false;
}