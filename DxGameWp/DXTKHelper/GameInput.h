#pragma once

#include <vector>
using namespace std;
using namespace Windows::Foundation;
using namespace Windows::System;

namespace DXTKHelper{
	struct InputPoint{
	public:
		InputPoint(int id,Point point):m_id(id),m_point(point){

		}
		int m_id;
		Point m_point;
	};

	struct InputKey{
	public:
		InputKey(VirtualKey key) :m_key(key){

		}
		VirtualKey m_key;

	};

	class GameInput{
	public:
		vector<InputPoint> m_pointInputs;
		vector<InputKey> m_keyInputs;

		void AddTouch(int id, Point point);
		void UpdateTouch(int id, Point point);
		void RemoveTouch(int id);

		void AddKey(VirtualKey key);
		void RemoveKey(VirtualKey key);
	};

}