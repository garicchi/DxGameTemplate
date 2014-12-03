#include "pch.h"
#include "SoundScreen.h"

#include "Renderer/TextureRenderer.h"


using namespace std;
using namespace DX;

SoundScreen::SoundScreen(const shared_ptr<DeviceResources>& deviceResources)
	:ScreenBase(deviceResources){

}

void SoundScreen::CreateResources(){
	ScreenBase::CreateResources();

	AddObject(shared_ptr<TextureRenderer>(new TextureRenderer(m_deviceResources, L"assets\\SmallLogo.png")));
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
	m_audioEngine=shared_ptr<AudioEngine>(new AudioEngine(eflags));
	m_soundEffect = shared_ptr<SoundEffect>(new SoundEffect(m_audioEngine.get(), L"Assets/sound.wav"));
	m_effectInstance = m_soundEffect->CreateInstance();

	m_effectInstance->Play(false);
	
}

void SoundScreen::ReleaseResources(){
	ScreenBase::ReleaseResources();
	
}

ScreenBase* SoundScreen::Update(StepTimer const &timer, const GameInput& input){
	ScreenBase::Update(timer,input);

	ScreenBase* nextScreen = this;

	//m_audioEngine->Update();

	return nextScreen;
}

void SoundScreen::Render(){
	ScreenBase::Render();
}