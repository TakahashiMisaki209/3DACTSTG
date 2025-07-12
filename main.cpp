//======================================================
// 
// window�\������
// Author:Takahashi Misaki
// 
//======================================================

#include "main.h"
#include "manager.h"

// �O���[�o���ϐ��錾
int g_nCountFPS = 0;

// �v���g�^�C�v�錾 ���ケ����R�s�[���Ďg��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM iParam);

//********************************************
//���C���֐�
//********************************************
// �R�s�[���Ďg���܂킷
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hinstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���������[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//���������[�N���m

	// �}�l�[�W���[�̃|�C���^����
	CManager* pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; // ��ʃT�C�Y�̍\����

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	// �}�l�[�W���[�̐���
	pManager = new CManager;

	// �}�l�[�W���[�̏���������
	pManager->Init(hInstance, hWnd, TRUE);

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���݂̎���
	DWORD dwCurentTime;
	// ���s����
	DWORD dwExeclastTime;

	// ����\��ݒ�
	timeBeginPeriod(1);
	dwCurentTime = 0;
	dwExeclastTime = timeGetTime();

	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwFPSLastTime;	// �Ō��FPS���v����������

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// window�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���

			dwCurentTime = timeGetTime();

			if ((dwCurentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�v��

				// FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurentTime;		// FPS�𑪒肵���Ƃ��̎�����ۑ�
				dwFrameCount = 0;					// �t���[���J�E���g���N���A

			}
			if ((dwCurentTime - dwExeclastTime) >= (1000 / 60))
			{// 60����1�b�o��

				dwExeclastTime = dwCurentTime;

				// �}�l�[�W���[�̍X�V����
				pManager->Update();

				// �}�l�[�W���[�̕`�揈��
				pManager->Draw();

				dwFrameCount++;		// �t���[���J�E���g�����Z
			}
		}
	}

	// �}�l�[�W���[�̔j��
	if (pManager != NULL)
	{
		// �I������
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//********************************************
//�E�C���h�E�v���V�[�W��
//********************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: // �E�B���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// �E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);  // ����̏�����Ԃ�
}