#pragma once
#include "stdafx.h"

class myInput
{
private:
	int controller_index = 0;//-1は不使用。0～15はgamepadのindex。16はキーボード。
	bool now_setting = false;//ボタン対応の変更中//未実装


	//仮想コントローラのボタン入力状況
	int myButton[17];
	double mySlidePad[4];
	double mySlidePad_deadzoon = 0.1;

	enum class myButton_num
	{
		Up, Down, Left, Right,
		A, B, X, Y,
		L, R, L2, R2,
		Home, Opt1, Opt2,
		PadL, PadR,

		size
	};
	enum class mySlidePad_num
	{
		LX, LY,
		RX, RY,
		rLX, rLY,
		rRX, rRY,

		size
	};
	enum class keyboard_num
	{
		a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
		n1, n2, n3, n4, n5, n6, n7, n8, n9, n0,
		Up, Down, Left, Right,
		Space, Shift, Enter, size

	};



	//入力の情報。押されている間は1。押されていない間は0。
	int gamepad_button[20] = {};
	double gamepad_axe[4] = {};//それぞれ-1.0～1.0
	int myKeyboard[(int)keyboard_num::size] = {};


	//controlerのカスタム用。-1は不使用。非負の数はenum myButton_numと(enum mySlidePad_num+100)に対応。
	int setting_gamepad_button[20] = {};
	int setting_gamepad_axe[8] = {};
	int setting_myKeyboard[(int)keyboard_num::size] = {};



public:
	myInput();
	myInput(int i);
	void ini_Input();
	void ini_setting();
	void ini_keyboard();
	void ini_joy_con_L();
	void ini_joy_con_R();
	void ini_joy_con_L2();
	void ini_joy_con_R2();
	void ini_kasai();
	void ini_SHIROUS();

	void update();
	void update_input();
	void update_input_keyboard();
	void update_input_controller();

	void update_myButton();


	void setting_controller();
	void save_setting_controller1();
	void load_setting_controller1();

	bool press_any_myButton();
	//押した瞬間は1。離した瞬間は-1。押している間はプラス。離している間は非正。
	int get_myButton(int num) { return myButton[num]; }
	int get_myButton_Up() { return myButton[(int)myButton_num::Up]; }
	int get_myButton_Down() { return myButton[(int)myButton_num::Down]; }
	int get_myButton_Left() { return myButton[(int)myButton_num::Left]; }
	int get_myButton_Right() { return myButton[(int)myButton_num::Right]; }
	int get_myButton_A() { return myButton[(int)myButton_num::A]; }
	int get_myButton_B() { return myButton[(int)myButton_num::B]; }
	int get_myButton_X() { return myButton[(int)myButton_num::X]; }
	int get_myButton_Y() { return myButton[(int)myButton_num::Y]; }
	int get_myButton_L() { return myButton[(int)myButton_num::L]; }
	int get_myButton_R() { return myButton[(int)myButton_num::R]; }
	int get_myButton_L2() { return myButton[(int)myButton_num::L2]; }
	int get_myButton_R2() { return myButton[(int)myButton_num::R2]; }
	int get_myButton_Home() { return myButton[(int)myButton_num::Home]; }
	int get_myButton_Opt1() { return myButton[(int)myButton_num::Opt1]; }
	int get_myButton_Opt2() { return myButton[(int)myButton_num::Opt2]; }
	int get_myButton_PadL() { return myButton[(int)myButton_num::PadL]; }
	int get_myButton_PadR() { return myButton[(int)myButton_num::PadR]; }

	double get_mySlidePad(int num) { return mySlidePad[num]; }
	double get_mySlidePad_LX() { return mySlidePad[(int)mySlidePad_num::LX]; }
	double get_mySlidePad_LY() { return mySlidePad[(int)mySlidePad_num::LY]; }
	double get_mySlidePad_RX() { return mySlidePad[(int)mySlidePad_num::RX]; }
	double get_mySlidePad_RY() { return mySlidePad[(int)mySlidePad_num::RY]; }
};
