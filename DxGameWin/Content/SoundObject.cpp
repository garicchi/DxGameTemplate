#include "pch.h"
#include "SoundObject.h"

using namespace std;
using namespace DX;

//�����_���[�̏������������s��
SoundObject::SoundObject(const shared_ptr<DeviceResources>& deviceResources,String^ path)
	:GameObject(deviceResources),m_path(path){


}

//�����_���[�Ŏg�����\�[�X���m�ۂ���
void SoundObject::CreateResources(){
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
	m_audioEngine = shared_ptr<AudioEngine>(new AudioEngine(eflags));
	m_soundEffect = shared_ptr<SoundEffect>(new SoundEffect(m_audioEngine.get(), m_path->Data()));
	m_effectInstance = m_soundEffect->CreateInstance();

}

//�����_���[�Ŏg�������\�[�X���������
void SoundObject::ReleaseResources(){
	if (m_effectInstance->GetState() == SoundState::PLAYING){
		m_effectInstance->Stop();
	}
	m_effectInstance.reset();

	m_audioEngine.reset();
	m_soundEffect.reset();
	
}

//�����_���[�̍X�V�������s��
void SoundObject::Update(const StepTimer& timer, const GameInput& input){
	m_audioEngine->Update();
}

//�����_���[�̕`�揈�����s��
void SoundObject::Render(){

}

void SoundObject::Play(){
	m_soundEffect->Play();
	
}