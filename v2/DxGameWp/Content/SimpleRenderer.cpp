#include "pch.h"
#include "SimpleRenderer.h"

using namespace std;
using namespace DX;

//�����_���[�̏������������s��
SimpleRenderer::SimpleRenderer(const shared_ptr<GameContext>& gameContext)
	:GameObject(gameContext){


}

void SimpleRenderer::WindowSizeChanged(){

}

//�����_���[�Ŏg�����\�[�X���m�ۂ���
void SimpleRenderer::CreateResources(){

}

//�����_���[�Ŏg�������\�[�X���������
void SimpleRenderer::ReleaseResources(){

}

//�����_���[�̍X�V�������s��
void SimpleRenderer::Update(shared_ptr<FrameContext>& frameContext){

}

//�����_���[�̕`�揈�����s��
void SimpleRenderer::Render(){

}