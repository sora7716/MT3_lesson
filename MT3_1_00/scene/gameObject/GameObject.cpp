#include"GameObject.h"

//倍率
void GameObject::Scale(bool front,bool behind){
	scale_.z += velocity_.z;
	//キー入力
	if (behind) {
		velocity_.z = 5.0f / 60.0f;
	}
	else if (front && scale_.x > 0.5f) {
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
void GameObject::TranslateX(bool bottom1,bool bottom2,float type){
	//キー入力
	if (bottom1) {
		velocity_.x = -5.0f / 60.0f * type;
	}
	else if (bottom2) {
		velocity_.x = 5.0f / 60.0f * type;
	}
	else { velocity_.x = 0.0f; }
}

void GameObject::TranslateY(bool bottom1, bool bottom2, float type){
	if (bottom1) {
		velocity_.y = 5.0f / 60.0f * type;
	}
	else if (bottom2) {
		velocity_.y = -5.0f / 60.0f * type;
	}
	else { velocity_.y = 0.0f; }
}

void GameObject::TranslateZ(bool bottom1, bool bottom2, float type){
	if (bottom1) {
		velocity_.z = 5.0f / 60.0f * type;
	}
	else if (bottom2) {
		velocity_.z = -5.0f / 60.0f * type;
	}
	else { velocity_.z = 0.0f; }
}

//移動をまとめた
void GameObject::Movement(bool left, bool right, bool up, bool down, bool front, bool behind, float type){
	translate_ += velocity_;//移動
	TranslateX(left, right, type);
	TranslateY(up, down, type);
	TranslateZ(front, behind, type);
}




