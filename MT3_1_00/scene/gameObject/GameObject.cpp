#include"GameObject.h"

//倍率
void GameObject::Scale(char front, char preFront, char behind, char preBehind){
	scale_ += velocity_;//拡縮
	//キー入力
	if (front && preFront) {
		velocity_.z = 5.0f / 60.0f;
	}
	else if (behind && preBehind && scale_.GetVector().x > 0.5f) {
		velocity_.z = -5.0f / 60.0f;
	}
	else { velocity_.z = 0.0f; }

}

//回転
void GameObject::Rotate(){
	rotate_ += radian_;//回転
	Novice::ScreenPrintf(0, 20, "%f", rotate_.GetVector().y);
}

//移動
void GameObject::Translate(char left, char preLeft,char right,char preRight,float direction){
	translate_ += velocity_;//移動
	//キー入力
	if (left && preLeft) {
		velocity_.x = -5.0f / 60.0f * direction;
	}
	else if (right && preRight) {
		velocity_.x = 5.0f / 60.0f * direction;
	}
	else { velocity_.x = 0.0f; }
}



