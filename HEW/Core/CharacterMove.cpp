#include "gamepad.h"
#include "Input.h"
#include "CharacterMove.h"
#include "Map.h"

namespace ziat {
	//キャラクターのビジュアルとか？
	void characterInitialize() {

	}

	// map の Groundtype::normal を「地面」として扱うジャンプ/落下
	// strong: ジャンプ初速（大きいほど高く跳ぶ）
	// gravity: 重力加速度（大きいほど早く落ちる）
	ziat::Character characterJump(int strong, int gravity) {
		using namespace ziat;

		static Character character_state{}; // 位置と nowjump を保持
		static int velocityY = 0;           // y方向速度（+で下、-で上）

		// map範囲内に丸める（範囲外アクセス防止）
		if (character_state.posx < 0) character_state.posx = 0;
		if (character_state.posx >= MAP_WIDTH) character_state.posx = MAP_WIDTH - 1;
		if (character_state.posy < 0) character_state.posy = 0;
		if (character_state.posy >= MAP_HEIGHT) character_state.posy = MAP_HEIGHT - 1;

		// 足元が地面か？
		const bool onGround = IsGroundAt(character_state.posx, character_state.posy + 1);

		// 地面にいるならジャンプ開始できる（この関数が呼ばれたら開始、という現仕様）
		if (!character_state.nowjump && onGround) {
			character_state.nowjump = true;
			velocityY = -strong; // 上向き初速（posyが下に増える座標系）
		}

		// ジャンプ中でなく、地面でもないなら落下開始
		if (!character_state.nowjump && !onGround) {
			// 落下中扱いに寄せる（velocityY を下向きに）
			if (velocityY < 0) velocityY = 0;
		}

		// 重力を適用（地面の上で停止しているなら 0 に）
		if (onGround && !character_state.nowjump) {
			velocityY = 0;
		}
		else {
			velocityY += gravity;
		}

		// 位置更新
		character_state.posy += velocityY;

		// 上に飛びすぎて範囲外を防ぐ
		if (character_state.posy < 0) {
			character_state.posy = 0;
			velocityY = 0;
		}
		if (character_state.posy >= MAP_HEIGHT) {
			character_state.posy = MAP_HEIGHT - 1;
			velocityY = 0;
			character_state.nowjump = false;
		}

		// めり込み補正：地面タイルに入っていたら、地面の1つ上まで戻す
		// （足元が地面＝posy+1 が地面になる位置が「着地位置」）
		while (character_state.posy + 1 < MAP_HEIGHT &&
			IsGroundAt(character_state.posx, character_state.posy)) {
			// キャラ座標そのものが地面判定される設計なら、ここは調整が必要
			// 今回は「地面タイル上にキャラが入ったら上に戻す」方針
			character_state.posy -= 1;
			velocityY = 0;
			character_state.nowjump = false;
			if (character_state.posy <= 0) break;
		}

		// 着地したらジャンプ終了（落下中に地面に乗った瞬間）
		if (IsGroundAt(character_state.posx, character_state.posy + 1) && velocityY >= 0) {
			character_state.nowjump = false;
			velocityY = 0;
		}

		return character_state;
	}
}