#include "pch.h"
#include "SimpleRenderer.h"

using namespace std;
using namespace DX;

//�����_���[�̏������������s��
SimpleRenderer::SimpleRenderer(const shared_ptr<DeviceResources>& deviceResources)
	:GameObject(deviceResources){


}

//�����_���[�Ŏg�����\�[�X���m�ۂ���
void SimpleRenderer::CreateResources(){

}

//�����_���[�Ŏg�������\�[�X���������
void SimpleRenderer::ReleaseResources(){

}

//�����_���[�̍X�V�������s��
void SimpleRenderer::Update(StepTimer const &timer, const GameInput& input){

}

//�����_���[�̕`�揈�����s��
void SimpleRenderer::Render(){

}