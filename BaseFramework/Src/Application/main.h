#pragma once

//============================================================
// アプリケーションクラス
//	APP.～ でどこからでもアクセス可能
//============================================================
class Application
{
// メンバ
public:

	// アプリケーション実行
	void Execute();

	// アプリケーション終了
	void End() { m_endFlag = true; }

	HWND GetWindowHandle() const { return m_window.GetWndHandle(); }
	int GetMouseWheelValue() const { return m_window.GetMouseWheelVal(); }

	int GetNowFPS() const { return m_fpsController.m_nowfps; }
	int GetMaxFPS() const { return m_fpsController.m_maxFps; }

private:

	void KdBeginUpdate();
	void PreUpdate();
	void Update();
	void PostUpdate();
	void KdPostUpdate();

	void KdBeginDraw(bool usePostProcess = true);
	void PreDraw();
	void Draw();
	void PostDraw();
	void DrawSprite();
	void KdPostDraw();

	// アプリケーション初期化
	bool Init(int w, int h);

	// アプリケーション解放
	void Release();

	// ゲームウィンドウクラス
	KdWindow		m_window;

	// FPSコントローラー
	KdFPSController	m_fpsController;

	// ゲーム終了フラグ trueで終了する
	bool		m_endFlag = false;

	////ルイズ!ルイズ!ルイズ!ルイズぅぅうううわぁああああああああああああああああああああああん!!!

	//あぁああああ…ああ…あっあっー!あぁああああああ!!!ルイズルイズルイズぅううぁわぁああああ!!!

	//	あぁクンカクンカ!クンカクンカ!スーハースーハー!スーハースーハー!いい匂いだなぁ…くんくん

	//	んはぁっ!ルイズ・フランソワーズたんの桃色ブロンドの髪をクンカクンカしたいお!クンカクンカ!あぁあ!!

	//	間違えた!モフモフしたいお!モフモフ!モフモフ!髪髪モフモフ!カリカリモフモフ…きゅんきゅんきゅい!!

	//	小説10巻のルイズたんかわいかったよぅ!!あぁぁああ…あああ…あっあぁああああ!!ふぁぁあああんんっ!!

	//	アニメ2期決まって良かったねルイズたん!あぁあああああ!かわいい!ルイズたん!かわいい!あっああぁああ!

	//	コミック1巻も発売されて嬉し…いやぁああああああ!!!にゃああああああああん!!ぎゃああああああああ!!

	//	ぐあああああああああああ!!!コミックなんて現実じゃない!!!!あ…小説もアニメもよく考えたら…

	//	ル イ ズ ち ゃ ん は 現実 じ ゃ な い ? にゃあああああああああああああん!!うぁああああああああああ!!

	//	そんなぁああああああ!!いやぁぁぁあああああああああ!!はぁああああああん!!ハルケギニアぁああああ!!

	//	この!ちきしょー!やめてやる!!現実なんかやめ…て…え!? 見…てる ? 表紙絵のルイズちゃんが僕を見てる ?

	//	表紙絵のルイズちゃんが僕を見てるぞ!ルイズちゃんが僕を見てるぞ!挿絵のルイズちゃんが僕を見てるぞ!!

	//	アニメのルイズちゃんが僕に話しかけてるぞ!!!よかった…世の中まだまだ捨てたモンじゃないんだねっ!

	//	いやっほぉおおおおおおお!!!僕にはルイズちゃんがいる!!やったよケティ!!ひとりでできるもん!!!

	//	あ、コミックのルイズちゃああああああああああああああん!!いやぁあああああああああああああああ!!!!

	//	あっあんああっああんあアン様ぁあ!!セ、セイバー!!シャナぁああああああ!!!ヴィルヘルミナぁあああ!!

	//	ううっうぅうう!!俺の想いよルイズへ届け!!ハルケギニアのルイズへ届け!俺は実はサイト萌えなんだっ!!

	int aho;

//=====================================================
// シングルトンパターン
//=====================================================
private:
	// 
	Application() {}

public:
	static Application &Instance(){
		static Application Instance;
		return Instance;
	}
};
