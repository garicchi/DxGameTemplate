#include "pch.h"
#include "SoundObject.h"

using namespace std;
using namespace DX;

//レンダラーの初期化処理を行う
SoundObject::SoundObject(const shared_ptr<DeviceResources>& deviceResources,String^ path)
	:GameObject(deviceResources),m_path(path){


}

//レンダラーで使うリソースを確保する
void SoundObject::CreateResources(){
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
	m_audioEngine = shared_ptr<AudioEngine>(new AudioEngine(eflags));
	m_soundEffect = shared_ptr<SoundEffect>(new SoundEffect(m_audioEngine.get(), m_path->Data()));
	m_effectInstance = m_soundEffect->CreateInstance();

}

//レンダラーで使ったリソースを解放する
void SoundObject::ReleaseResources(){
	if (m_effectInstance->GetState() == SoundState::PLAYING){
		m_effectInstance->Stop();
	}
	m_effectInstance.reset();

	m_audioEngine.reset();
	m_soundEffect.reset();
	
}

//レンダラーの更新処理を行う
void SoundObject::Update(const StepTimer& timer, const GameInput& input){
	m_audioEngine->Update();
}

//レンダラーの描画処理を行う
void SoundObject::Render(){

}

void SoundObject::Play(){
	m_soundEffect->Play();
	
}