#pragma once

// シーンから次の遷移先を返すための列挙型
enum class SceneName {
    None,   // 遷移なし（今のシーンを維持）
    Title,  // タイトルへ
    Setting,// 設定画面
    Game,   // ゲーム本編へ
    Exit    // ゲーム終了
};

class IScene {
public:
    virtual ~IScene() {}

    //初期化処理
    virtual void Initialize() = 0;

    // 更新処理
    virtual SceneName Update() = 0;

    //描画処理
    virtual void Draw() = 0;
};