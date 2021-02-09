#pragma once
#include<iostream>
#include <GL/gl3w.h> 
#include <GLFW/glfw3.h>

//�E�B���h�E�֘A�̏���
class Window {
	//�E�B���h�E�̃n���h��
	GLFWwindow* const window;

	//�E�B���h�E�̃T�C�Y
	GLfloat size[2];

	//���[���h���W�n�ɑ΂���f�o�C�X���W�n�̊g�嗦
	GLfloat scale;

	//�}�`�̐��K���f�o�C�X���W�n��ł̈ʒu
	GLfloat location[2];



public:
	//�R���X�g���N�^
	Window(int width = 1280, int height = 720, const char* title = "Window") :
		window(glfwCreateWindow(width, height, title, NULL, NULL)) 
		,scale(100.0f)
	{

		if (window == NULL)
		{
			//�E�B���h�E���쐬�ł��Ȃ�����
			std::cerr << "Can't create GLFW window." << std::endl;
			exit(1);
		}

		//���݂̃E�B���h�E�������Ώۂɂ���֐�
		glfwMakeContextCurrent(window);

		//GLEW������������
		if (gl3wInit()) {
			//GLEW�̏������Ɏ��s����
			std::cerr << "Can't initialize GLEW" << std::endl;
			exit(1);
		}

		//���������̃^�C�~���O��҂�
		//�J���[�o�b�t�@�̓���ւ��̃^�C�~���O���w�肷��
		glfwSwapInterval(1);

		//�E�B���h�E�T�C�Y�ύX���ɌĂяo�������̓o�^
		glfwSetWindowSizeCallback(window, resize);

		//���̃C���X�^���X��this�|�C���^���L�^���Ă���
		glfwSetWindowUserPointer(window, this);

		//�J�����E�B���h�E�̏����ݒ�
		resize(window, width, height);
	}

	//�f�X�g���N�^
	virtual ~Window() {
		glfwDestroyWindow(window);
	}

	//�`�惋�[�v�̌p������
	explicit operator bool() {
		//�C�x���g�����o��
		glfwWaitEvents();

		//�E�B���h�E�����K�v���Ȃ����true��Ԃ�
		return !glfwWindowShouldClose(window);
	}

	//�_�u���o�b�t�@�����O
	void swapBuffers() const {
		//�J���[�o�b�t�@�����ւ���
		glfwSwapBuffers(window);
	}

	//�E�B���h�E�̃T�C�Y�ύX���̏���
	static void resize(GLFWwindow* const window, int width, int height) {
		//�t���[���o�b�t�@�̃T�C�Y�𒲂ׂ�
		int fbWidth, fbHeight;
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		//�t���[���o�b�t�@�S�̂��r���[�|�[�g�ɐݒ肷��
		glViewport(0, 0, fbWidth, fbHeight);

		//���̃C���X�^���X��this�|�C���^�𓾂�
		Window* const
			instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
		if (instance != NULL) {
			
			//�J�����E�B���h�E�̃T�C�Y��ۑ�����
			instance->size[0] = static_cast<GLfloat>(width);
			instance->size[1] = static_cast<GLfloat>(height);
		}
	}

	//�E�B���h�E�̃T�C�Y�����o��
	const GLfloat* getSize() const { return size; }

	//���[���h���W�n�ɑ΂���f�o�C�X���W�n�̊g�嗦�����o��
	GLfloat getScale() const { return scale; }

	//window�����o��
	GLFWwindow* getWindow() const { return window; }
};