#include "pch.h"
#include "GameInput.h"

namespace DXTKHelper{
	void GameInput::AddTouch(int id, Point point){
		int i = 0;
		for (vector<InputPoint>::iterator ite = m_pointInputs.begin(); ite < m_pointInputs.end(); ite++, i++){
			if (m_pointInputs.at(i).m_id == id){
				return;
			}
		}
		m_pointInputs.push_back(InputPoint(id,point));
	}

	void GameInput::UpdateTouch(int id, Point point){
		for (unsigned int i = 0; i < m_pointInputs.size(); i++){
			if (m_pointInputs.at(i).m_id == id){
				m_pointInputs.at(i).m_point = point;
				break;
			}
		}
	}

	void GameInput::RemoveTouch(int id){
		int i = 0;
		for (vector<InputPoint>::iterator ite = m_pointInputs.begin(); ite < m_pointInputs.end(); ite++, i++){
			if (m_pointInputs.at(i).m_id == id){
				m_pointInputs.erase(ite);
				break;
			}
		}
	}

	void GameInput::AddKey(VirtualKey key){
		int i = 0;
		for (vector<InputKey>::iterator ite = m_keyInputs.begin(); ite < m_keyInputs.end(); ite++, i++){
			if (m_keyInputs.at(i).m_key == key){
				return;
			}
		}
		m_keyInputs.push_back(InputKey(key));
	}
	

	void GameInput::RemoveKey(VirtualKey key){
		int i = 0;
		for (vector<InputKey>::iterator ite = m_keyInputs.begin(); ite < m_keyInputs.end(); ite++, i++){
			if (m_keyInputs.at(i).m_key == key){
				m_keyInputs.erase(ite);
				break;
			}
			
		}
	}
	
}