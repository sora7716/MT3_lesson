#include"GameObject.h"

//倍率
void GameObject::Scale(bool front,bool behind){
	scale_.SetVector({ scale_.GetVector().x+velocity_.z,scale_.GetVector().y + velocity_.z,scale_.GetVector().z + velocity_.z });
	//キー入力
	if (behind) {
		velocity_.z = 5.0f / 60.0f;
	}
	else if (front && scale_.GetVector().x > 0.5f) {
		velocity_.z = -5.0f / 60.0f;
	}
	else { velocity_.z = 0.0f; }

}

//回転
void GameObject::Rotate(){
	rotate_ += radian_;//回転
	//Novice::ScreenPrintf(0, 20, "%f", rotate_.GetVector().y);
}

//移動
void GameObject::Translate(bool left,bool right,float direction){
	translate_ += velocity_;//移動
	//キー入力
	if (left) {
		velocity_.x = -5.0f / 60.0f * direction;
	}
	else if (right) {
		velocity_.x = 5.0f / 60.0f * direction;
	}
	else { velocity_.x = 0.0f; }
}



