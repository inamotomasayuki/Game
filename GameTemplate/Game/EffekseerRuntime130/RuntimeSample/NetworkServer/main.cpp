
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <d3d9.h>
#include <XAudio2.h>
#pragma comment(lib, "d3d9.lib" )

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#if _DEBUG
#pragma comment(lib, "VS2013/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2013/Debug/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2013/Debug/EffekseerSoundXAudio2.lib" )
#else
#pragma comment(lib, "VS2013/Release/Effekseer.lib" )
#pragma comment(lib, "VS2013/Release/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2013/Release/EffekseerSoundXAudio2.lib" )
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static HWND g_window_handle = NULL;
static int g_window_width = 800;
static int g_window_height = 600;
static ::Effekseer::Manager*			g_manager = NULL;
static ::EffekseerRenderer::Renderer*	g_renderer = NULL;
static ::EffekseerSound::Sound*			g_sound = NULL;
static ::Effekseer::Effect*				g_effect = NULL;
static ::Effekseer::Handle				g_handle = -1;
static ::Effekseer::Vector3D			g_position;

static LPDIRECT3D9						g_d3d = NULL;
static LPDIRECT3DDEVICE9				g_d3d_device = NULL;
static IXAudio2*						g_xa2 = NULL;
static IXAudio2MasteringVoice*			g_xa2_master = NULL;

static ::Effekseer::Server*				g_server = NULL;

static int32_t							g_timer = 0;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg ) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void InitWindow()
{
	WNDCLASS wndClass;
	wchar_t szClassNme[]      =  L"RuntimeSample";
	wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc   = WndProc;
	wndClass.cbClsExtra    = 0;
	wndClass.cbWndExtra    = 0;
	wndClass.hInstance     = GetModuleHandle(0);
	wndClass.hIcon         = NULL;
	wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName  = NULL;
	wndClass.lpszClassName = szClassNme;
	RegisterClass(&wndClass);
	g_window_handle = CreateWindow(
		szClassNme,
		L"RuntimeSample",
		WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		g_window_width,
		g_window_height,
		NULL,
		NULL,
		GetModuleHandle(0),
		NULL);
	ShowWindow( g_window_handle, true );
	UpdateWindow( g_window_handle );
	
	// COM????????
	CoInitializeEx( NULL, NULL );

	// DirectX9???????????s??
	D3DPRESENT_PARAMETERS d3dp;
	ZeroMemory(&d3dp, sizeof(d3dp));
	d3dp.BackBufferWidth = g_window_width;
	d3dp.BackBufferHeight = g_window_height;
	d3dp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dp.BackBufferCount = 1;      
	d3dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dp.Windowed = TRUE;
	d3dp.hDeviceWindow = g_window_handle;
	d3dp.EnableAutoDepthStencil = TRUE;
    d3dp.AutoDepthStencilFormat = D3DFMT_D16;

	g_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	
	g_d3d->CreateDevice( 
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dp,
		&g_d3d_device );
	
	// XAudio2???????????s??
	XAudio2Create( &g_xa2 );

	g_xa2->CreateMasteringVoice( &g_xa2_master );
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void MainLoop()
{
	for(;;)
	{ 
		MSG msg;
		if (PeekMessage (&msg,NULL,0,0,PM_NOREMOVE)) 
		{
			if( msg.message == WM_QUIT )
			{
				return ;
			}
			GetMessage (&msg,NULL,0,0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ?T?[?o?[???X?V???s???B
			g_server->Update();

			if( g_timer % 120 == 0 )
			{
				// ?G?t?F?N?g?????~
				g_manager->StopEffect( g_handle );

				// ?G?t?F?N?g??????
				g_handle = g_manager->Play( g_effect, 0, 0, 0 );
			}

			// ?G?t?F?N?g?????????????s???B
			g_manager->AddLocation( g_handle, ::Effekseer::Vector3D( 0.2f, 0.0f, 0.0f ) );

			// ?G?t?F?N?g???X?V???????s???B
			g_manager->Update();
			
			
			g_d3d_device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
			g_d3d_device->BeginScene();

			// ?G?t?F?N?g???`???J?n???????s???B
			g_renderer->BeginRendering();

			// ?G?t?F?N?g???`?????s???B
			g_manager->Draw();

			// ?G?t?F?N?g???`???I?????????s???B
			g_renderer->EndRendering();

			g_d3d_device->EndScene();

			g_timer++;

			{
				HRESULT hr;
				hr = g_d3d_device->Present( NULL, NULL, NULL, NULL );

				// ?f?o?C?X???X?g????
				switch ( hr )
				{
					// ?f?o?C?X???X?g
					case D3DERR_DEVICELOST:
					while ( FAILED( hr = g_d3d_device->TestCooperativeLevel() ) )
					{
						switch ( hr )
						{
							// ?f?o?C?X???X?g
							case D3DERR_DEVICELOST:
								::SleepEx( 1000, true );
								break;

							// ?f?o?C?X???X?g?F???Z?b?g??
							case D3DERR_DEVICENOTRESET:
								
								// ?f?o?C?X???X?g?????????s???O?????s????
								g_renderer->OnLostDevice();

								D3DPRESENT_PARAMETERS d3dp;
								ZeroMemory(&d3dp, sizeof(d3dp));
								d3dp.BackBufferWidth = g_window_width;
								d3dp.BackBufferHeight = g_window_height;
								d3dp.BackBufferFormat = D3DFMT_X8R8G8B8;
								d3dp.BackBufferCount = 1;      
								d3dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
								d3dp.Windowed = TRUE;
								d3dp.hDeviceWindow = g_window_handle;
								d3dp.EnableAutoDepthStencil = TRUE;
								d3dp.AutoDepthStencilFormat = D3DFMT_D16;

								g_d3d_device->Reset( &d3dp );

								// ?f?o?C?X???X?g???????????????s????
								g_renderer->OnResetDevice();

								break;
						}
					}
					break;
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
int main()
{
	InitWindow();

	// ?`???p?C???X?^???X??????
	g_renderer = ::EffekseerRendererDX9::Renderer::Create( g_d3d_device, 2000 );
	
	// ?G?t?F?N?g?????p?C???X?^???X??????
	g_manager = ::Effekseer::Manager::Create( 2000 );

	// ?`???p?C???X?^???X?????`???@?\??????
	g_manager->SetSpriteRenderer( g_renderer->CreateSpriteRenderer() );
	g_manager->SetRibbonRenderer( g_renderer->CreateRibbonRenderer() );
	g_manager->SetRingRenderer( g_renderer->CreateRingRenderer() );
	g_manager->SetModelRenderer( g_renderer->CreateModelRenderer() );

	// ?`???p?C???X?^???X?????e?N?X?`?????????@?\??????
	// ?????g?????\?A???????t?@?C?????????????????????B
	g_manager->SetTextureLoader( g_renderer->CreateTextureLoader() );
	g_manager->SetModelLoader( g_renderer->CreateModelLoader() );

	// ???????p?C???X?^???X??????
	g_sound = ::EffekseerSound::Sound::Create( g_xa2, 16, 16 );

	// ???????p?C???X?^???X?????????@?\???w??
	g_manager->SetSoundPlayer( g_sound->CreateSoundPlayer() );
	
	// ???????p?C???X?^???X?????T?E???h?f?[?^???????@?\??????
	// ?????g?????\?A???????t?@?C?????????????????????B
	g_manager->SetSoundLoader( g_sound->CreateSoundLoader() );

	// ?T?[?o?[??????
	g_server = Effekseer::Server::Create();

	// ?T?[?o?[???|?[?g60000???J?n
	g_server->Start( 60000 );
	
	// ???_???u???m??
	g_position = ::Effekseer::Vector3D( 10.0f, 5.0f, 20.0f );

	// ???e?s????????
	g_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovRH( 90.0f / 180.0f * 3.14f, (float)g_window_width / (float)g_window_height, 1.0f, 50.0f ) );

	// ?J?????s????????
	g_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtRH( g_position, ::Effekseer::Vector3D( 0.0f, 0.0f, 0.0f ), ::Effekseer::Vector3D( 0.0f, 1.0f, 0.0f ) ) );
	
	// ?G?t?F?N?g??????
	g_effect = Effekseer::Effect::Create( g_manager, (const EFK_CHAR*)L"test.efk" );

	// ???W?????t?@?C????test.efkproj???????????A?G?t?F?N?g??test?????????????o?^
	g_server->Regist( (const EFK_CHAR*)L"test", g_effect );

	MainLoop();

	// ?G?t?F?N?g???j??
	ES_SAFE_RELEASE( g_effect );

	// ?T?[?o?[???j??
	ES_SAFE_DELETE( g_server );

	// ?????G?t?F?N?g?????p?C???X?^???X???j??
	g_manager->Destroy();

	// ???????????p?C???X?^???X???j??
	g_sound->Destroy();

	// ?????`???p?C???X?^???X???j??
	g_renderer->Destroy();

	// XAudio2??????
	if( g_xa2_master != NULL )
	{
		g_xa2_master->DestroyVoice();
		g_xa2_master = NULL;
	}
	ES_SAFE_RELEASE( g_xa2 );

	// DirectX??????
	ES_SAFE_RELEASE( g_d3d_device );
	ES_SAFE_RELEASE( g_d3d );

	// COM???I??????
	CoUninitialize();

	return 0;
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------