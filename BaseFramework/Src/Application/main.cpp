﻿#include "main.h"

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// エントリーポイント
// アプリケーションはこの関数から進行する
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_  HINSTANCE, _In_ LPSTR , _In_ int)
{
	// メモリリークを知らせる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// COM初期化
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		CoUninitialize();

		return 0;
	}

	// mbstowcs_s関数で日本語対応にするために呼ぶ
	setlocale(LC_ALL, "japanese");

	//===================================================================
	// 実行
	//===================================================================
	Application::Instance().Execute();

	// COM解放
	CoUninitialize();

	return 0;
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新開始
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::KdBeginUpdate()
{
	// 入力状況の更新
	KdInputManager::Instance().Update();

	// 空間環境の更新
	KdShaderManager::Instance().WorkAmbientController().Update();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新終了
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::KdPostUpdate()
{
	// 3DSoundListnerの行列を更新
	KdAudioManager::Instance().SetListnerMatrix(KdShaderManager::Instance().GetCameraCB().mView.Invert());
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新の前処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PreUpdate()
{
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::Update()
{
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション更新の後処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PostUpdate()
{
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画開始
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::KdBeginDraw(bool usePostProcess)
{
	KdDirect3D::Instance().ClearBackBuffer();

	KdShaderManager::Instance().WorkAmbientController().Draw();

	if (!usePostProcess) return;
	KdShaderManager::Instance().m_postProcessShader.Draw();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画終了
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::KdPostDraw()
{
	// BackBuffer -> 画面表示
	KdDirect3D::Instance().WorkSwapChain()->Present(0, 0);
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画の前処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PreDraw()
{
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::Draw()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光を遮るオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_StandardShader.BeginGenerateDepthMapFromLight();
	{
	}
	KdShaderManager::Instance().m_StandardShader.EndGenerateDepthMapFromLight();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のあるオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_StandardShader.BeginLit();
	{
	}
	KdShaderManager::Instance().m_StandardShader.EndLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のないオブジェクト(透明な部分を含む物体やエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_StandardShader.BeginUnLit();
	{
	}
	KdShaderManager::Instance().m_StandardShader.EndUnLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光源オブジェクト(自ら光るオブジェクトやエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_postProcessShader.BeginBright();
	{
	}
	KdShaderManager::Instance().m_postProcessShader.EndBright();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション描画の後処理
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::PostDraw()
{
	// 画面のぼかしや被写界深度処理の実施
	KdShaderManager::Instance().m_postProcessShader.PostEffectProcess();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// 2Dスプライトの描画
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::DrawSprite()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 2Dの描画はこの間で行う
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
	}
	KdShaderManager::Instance().m_spriteShader.End();
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション初期設定
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
bool Application::Init(int w, int h)
{
	//===================================================================
	// ウィンドウ作成
	//===================================================================
	if (m_window.Create(w, h, "3D GameProgramming", "Window") == false) {
		MessageBoxA(nullptr, "ウィンドウ作成に失敗", "エラー", MB_OK);
		return false;
	}

	//===================================================================
	// フルスクリーン確認
	//===================================================================
	bool bFullScreen = false;
	if (MessageBoxA(m_window.GetWndHandle(), "フルスクリーンにしますか？", "確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		bFullScreen = true;
	}

	//===================================================================
	// Direct3D初期化
	//===================================================================

	// デバイスのデバッグモードを有効にする
	bool deviceDebugMode = false;
#ifdef _DEBUG
	deviceDebugMode = true;
#endif

	// Direct3D初期化
	std::string errorMsg;
	if (KdDirect3D::Instance().Init(m_window.GetWndHandle(), w, h, deviceDebugMode, errorMsg) == false) {
		MessageBoxA(m_window.GetWndHandle(), errorMsg.c_str(), "Direct3D初期化失敗", MB_OK | MB_ICONSTOP);
		return false;
	}

	// フルスクリーン設定
	if (bFullScreen) {
		HRESULT hr;

		hr = KdDirect3D::Instance().SetFullscreenState(TRUE, 0);
		if (FAILED(hr))
		{
			MessageBoxA(m_window.GetWndHandle(), "フルスクリーン設定失敗", "Direct3D初期化失敗", MB_OK | MB_ICONSTOP);
			return false;
		}
	}

	//===================================================================
	// シェーダー初期化
	//===================================================================
	KdShaderManager::Instance().Init();

	//===================================================================
	// オーディオ初期化
	//===================================================================
	KdAudioManager::Instance().Init();

	////諸君　私は戦争が好きだ
	//諸君　私は戦争が好きだ
	//	諸君　私は戦争が大好きだ

	//	殲滅戦が好きだ
	//	電撃戦が好きだ
	//	打撃戦が好きだ
	//	防衛戦が好きだ
	//	包囲戦が好きだ
	//	突破戦が好きだ
	//	退却戦が好きだ
	//	掃討戦が好きだ
	//	撤退戦が好きだ

	//	平原で　街道で
	//	塹壕で　草原で
	//	凍土で　砂漠で
	//	海上で　空中で
	//	泥中で　湿原で

	//	この地上で行われるありとあらゆる戦争行動が大好きだ

	//	戦列をならべた砲兵の一斉発射が轟音と共に敵陣を吹き飛ばすのが好きだ
	//	空中高く放り上げられた敵兵が効力射でばらばらになった時など心がおどる
	//	戦車兵の操るティーゲルの88ｍｍアハトアハトが敵戦車を撃破するのが好きだ
	//	悲鳴を上げて燃えさかる戦車から飛び出してきた敵兵をMGでなぎ倒した時など胸がすくような気持ちだった

	//	銃剣先をそろえた歩兵の横隊が敵の戦列を蹂躙するのが好きだ
	//	恐慌状態の新兵が既に息絶えた敵兵を何度も何度も刺突している様など感動すら覚える

	//	敗北主義の逃亡兵達を街灯上に吊るし上げていく様などはもうたまらない
	//	泣き叫ぶ捕虜達が私の振り下ろした手の平とともに金切り声を上げるシュマイザーにばたばたと薙ぎ倒されるのも最高だ
	//	哀れな抵抗者達レジスタンスが雑多な小火器で健気にも立ち上がってきたのを80cm列車砲ドーラの4.8t榴爆弾が都市区画ごと木端微塵に粉砕した時など絶頂すら覚える

	//	露助の機甲師団に滅茶苦茶にされるのが好きだ
	//	必死に守るはずだった村々が蹂躙され女子供が犯され殺されていく様はとてもとても悲しいものだ
	//	英米の物量に押し潰されて殲滅されるのが好きだ
	//	英米攻撃機ヤーボに追いまわされ害虫の様に地べたを這い回るのは屈辱の極みだ

	//	諸君　私は戦争を地獄の様な戦争を望んでいる
	//	諸君　私に付き従う大隊戦友諸君
	//	君達は一体何を望んでいる？

	//	更なる戦争を望むか？
	//	情け容赦のない糞の様な戦争を望むか？
	//	鉄風雷火の限りを尽くし三千世界の鴉を殺す嵐の様な闘争を望むか？
	//	『戦争！クリーク　戦争！クリーク　戦争！クリーク』
	//	よろしい　ならば戦争クリークだ

	//	我々は満身の力をこめて今まさに振り降ろさんとする握り拳だ
	//	だがこの暗い闇の底で半世紀もの間堪え続けてきた我々にただの戦争ではもはや足りない！！

	//	大戦争を！！
	//	一心不乱の大戦争を！！

	//	我らはわずかに一個大隊　千人に満たぬ敗残兵に過ぎない
	//	だが諸君は一騎当千の古強者だと私は信仰している
	//	ならば我らは諸君と私で総力100万と1人の軍集団となる

	//	我々を忘却の彼方へと追いやり眠りこけている連中を叩き起こそう
	//	髪の毛をつかんで引きずり降ろし眼を開けさせ思い出させよう
	//	連中に恐怖の味を思い出させてやる
	//	連中に我々の軍靴の音を思い出させてやる

	//	天と地のはざまには奴らの哲学では思いもよらない事があることを思い出させてやる

	//	一千人の吸血鬼の戦闘団カンプグルッペで世界を燃やし尽くしてやる

	//	～原作版～

	//	全フラッペン　発動開始　旗艦デクス・ウキス・マキーネ　始動

	//	離床！！　全ワイヤー　全索引線　解除
	//	「最後の大隊　大隊指揮官より　全空中艦隊へ」
	//	目標　英国本土　ロンドン首都上空！！

	//	第二次ゼーレーヴェあしか作戦　状況を開始せよ
	//	征くぞ　諸君

	//	～OVA版～

	//	そうだ　あれが待ちに望んだ欧州の光だ

	//	私は諸君らを約束通り連れて帰ったぞ　あの懐かしの戦場へ　あの懐かしの戦争へ

	//	『少佐殿！少佐！代行！代行殿！大隊指揮官殿！』

	//	そしてゼーレーヴェはついに大洋を渡り丘へと登る

	//	ミレニアム大隊各員に伝達　大隊長命令である

	//	さぁ　諸君

	//	地獄を創るぞ
	aho = 1;

	return true;
}

// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
// アプリケーション実行
// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void Application::Execute()
{
	KdCSVData windowData("Asset/Data/WindowSettings.csv");
	const std::vector<std::string>& sizeData = windowData.GetLine(0);

	//===================================================================
	// 初期設定(ウィンドウ作成、Direct3D初期化など)
	//===================================================================
	if (Application::Instance().Init(atoi(sizeData[0].c_str()), atoi(sizeData[1].c_str())) == false) {
		return;
	}

	//===================================================================
	// ゲームループ
	//===================================================================

	// 時間
	m_fpsController.Init();

	// ループ
	while (1)
	{
		// 処理開始時間Get
		m_fpsController.UpdateStartTime();

		// ゲーム終了指定があるときはループ終了
		if (m_endFlag)
		{
			break;
		}

		//=========================================
		//
		// ウィンドウ関係の処理
		//
		//=========================================

		// ウィンドウのメッセージを処理する
		m_window.ProcessMessage();

		// ウィンドウが破棄されてるならループ終了
		if (m_window.IsCreated() == false)
		{
			break;
		}

		if (GetAsyncKeyState(VK_ESCAPE))
		{
//			if (MessageBoxA(m_window.GetWndHandle(), "本当にゲームを終了しますか？",
//				"終了確認", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
			{
				End();
			}
		}
		//=========================================
		//
		// アプリケーション更新処理
		//
		//=========================================

		KdBeginUpdate();
		{
			PreUpdate();

			Update();

			PostUpdate();
		}
		KdPostUpdate();

		//=========================================
		//
		// アプリケーション描画処理
		//
		//=========================================

		KdBeginDraw();
		{
			PreDraw();

			Draw();

			PostDraw();

			DrawSprite();
		}
		KdPostDraw();

		//=========================================
		//
		// フレームレート制御
		//
		//=========================================

		m_fpsController.Update();
	}

	//===================================================================
	// アプリケーション解放
	//===================================================================
	Release();
}

// アプリケーション終了
void Application::Release()
{
	KdInputManager::Instance().Release();

	KdShaderManager::Instance().Release();

	KdAudioManager::Instance().Release();

	KdDirect3D::Instance().Release();

	// ウィンドウ削除
	m_window.Release();
}
