#include"myInput.h"

myInput::myInput()
{
	controller_index = 16;
	ini_Input();
	ini_SHIROUS();
}
myInput::myInput(int i)
{
	controller_index = i;
	ini_Input();
	//ini_kasai();
	//ini_joy_con_L();
	//if (i == 0)ini_joy_con_L2();
	//if (i == 1)ini_joy_con_R2();
	//ini_keyboard();
	ini_SHIROUS();
}

void myInput::update()
{
	update_input();
	update_myButton();
}
void myInput::update_input()
{
	if (controller_index == -1)
	{
		return;
	}
	else if (controller_index == 16)
	{
		update_input_keyboard();
	}
	else
	{
		update_input_controller();
	}
}
void myInput::update_input_keyboard()
{
	if (KeyA.pressed())myKeyboard[(int)keyboard_num::a] = 1;
	else myKeyboard[(int)keyboard_num::a] = 0;

	if (KeyB.pressed())myKeyboard[(int)keyboard_num::b] = 1;
	else myKeyboard[(int)keyboard_num::b] = 0;

	if (KeyC.pressed())myKeyboard[(int)keyboard_num::c] = 1;
	else myKeyboard[(int)keyboard_num::c] = 0;

	if (KeyD.pressed())myKeyboard[(int)keyboard_num::d] = 1;
	else myKeyboard[(int)keyboard_num::d] = 0;

	if (KeyE.pressed())myKeyboard[(int)keyboard_num::e] = 1;
	else myKeyboard[(int)keyboard_num::e] = 0;

	if (KeyF.pressed())myKeyboard[(int)keyboard_num::f] = 1;
	else myKeyboard[(int)keyboard_num::f] = 0;

	if (KeyG.pressed())myKeyboard[(int)keyboard_num::g] = 1;
	else myKeyboard[(int)keyboard_num::g] = 0;

	if (KeyH.pressed())myKeyboard[(int)keyboard_num::h] = 1;
	else myKeyboard[(int)keyboard_num::h] = 0;

	if (KeyI.pressed())myKeyboard[(int)keyboard_num::i] = 1;
	else myKeyboard[(int)keyboard_num::i] = 0;

	if (KeyJ.pressed())myKeyboard[(int)keyboard_num::j] = 1;
	else myKeyboard[(int)keyboard_num::j] = 0;

	if (KeyK.pressed())myKeyboard[(int)keyboard_num::k] = 1;
	else myKeyboard[(int)keyboard_num::k] = 0;

	if (KeyL.pressed())myKeyboard[(int)keyboard_num::l] = 1;
	else myKeyboard[(int)keyboard_num::l] = 0;

	if (KeyM.pressed())myKeyboard[(int)keyboard_num::m] = 1;
	else myKeyboard[(int)keyboard_num::m] = 0;

	if (KeyN.pressed())myKeyboard[(int)keyboard_num::n] = 1;
	else myKeyboard[(int)keyboard_num::n] = 0;

	if (KeyO.pressed())myKeyboard[(int)keyboard_num::o] = 1;
	else myKeyboard[(int)keyboard_num::o] = 0;

	if (KeyP.pressed())myKeyboard[(int)keyboard_num::p] = 1;
	else myKeyboard[(int)keyboard_num::p] = 0;

	if (KeyQ.pressed())myKeyboard[(int)keyboard_num::q] = 1;
	else myKeyboard[(int)keyboard_num::q] = 0;

	if (KeyR.pressed())myKeyboard[(int)keyboard_num::r] = 1;
	else myKeyboard[(int)keyboard_num::r] = 0;

	if (KeyS.pressed())myKeyboard[(int)keyboard_num::s] = 1;
	else myKeyboard[(int)keyboard_num::s] = 0;

	if (KeyT.pressed())myKeyboard[(int)keyboard_num::t] = 1;
	else myKeyboard[(int)keyboard_num::t] = 0;

	if (KeyU.pressed())myKeyboard[(int)keyboard_num::u] = 1;
	else myKeyboard[(int)keyboard_num::u] = 0;

	if (KeyV.pressed())myKeyboard[(int)keyboard_num::v] = 1;
	else myKeyboard[(int)keyboard_num::v] = 0;

	if (KeyW.pressed())myKeyboard[(int)keyboard_num::w] = 1;
	else myKeyboard[(int)keyboard_num::w] = 0;

	if (KeyX.pressed())myKeyboard[(int)keyboard_num::x] = 1;
	else myKeyboard[(int)keyboard_num::x] = 0;

	if (KeyY.pressed())myKeyboard[(int)keyboard_num::y] = 1;
	else myKeyboard[(int)keyboard_num::y] = 0;

	if (KeyZ.pressed())myKeyboard[(int)keyboard_num::z] = 1;
	else myKeyboard[(int)keyboard_num::z] = 0;


	if (Key1.pressed())myKeyboard[(int)keyboard_num::n1] = 1;
	else myKeyboard[(int)keyboard_num::n1] = 0;

	if (Key2.pressed())myKeyboard[(int)keyboard_num::n2] = 1;
	else myKeyboard[(int)keyboard_num::n2] = 0;

	if (Key3.pressed())myKeyboard[(int)keyboard_num::n3] = 1;
	else myKeyboard[(int)keyboard_num::n3] = 0;

	if (Key4.pressed())myKeyboard[(int)keyboard_num::n4] = 1;
	else myKeyboard[(int)keyboard_num::n4] = 0;

	if (Key5.pressed())myKeyboard[(int)keyboard_num::n5] = 1;
	else myKeyboard[(int)keyboard_num::n5] = 0;

	if (Key6.pressed())myKeyboard[(int)keyboard_num::n6] = 1;
	else myKeyboard[(int)keyboard_num::n6] = 0;

	if (Key7.pressed())myKeyboard[(int)keyboard_num::n7] = 1;
	else myKeyboard[(int)keyboard_num::n7] = 0;

	if (Key8.pressed())myKeyboard[(int)keyboard_num::n8] = 1;
	else myKeyboard[(int)keyboard_num::n8] = 0;

	if (Key9.pressed())myKeyboard[(int)keyboard_num::n9] = 1;
	else myKeyboard[(int)keyboard_num::n9] = 0;

	if (Key0.pressed())myKeyboard[(int)keyboard_num::n0] = 1;
	else myKeyboard[(int)keyboard_num::n0] = 0;


	if (KeyUp.pressed())myKeyboard[(int)keyboard_num::Up] = 1;
	else myKeyboard[(int)keyboard_num::Up] = 0;

	if (KeyDown.pressed())myKeyboard[(int)keyboard_num::Down] = 1;
	else myKeyboard[(int)keyboard_num::Down] = 0;

	if (KeyLeft.pressed())myKeyboard[(int)keyboard_num::Left] = 1;
	else myKeyboard[(int)keyboard_num::Left] = 0;

	if (KeyRight.pressed())myKeyboard[(int)keyboard_num::Right] = 1;
	else myKeyboard[(int)keyboard_num::Right] = 0;


	if (KeySpace.pressed())myKeyboard[(int)keyboard_num::Space] = 1;
	else myKeyboard[(int)keyboard_num::Space] = 0;

	if (KeyShift.pressed())myKeyboard[(int)keyboard_num::Shift] = 1;
	else myKeyboard[(int)keyboard_num::Shift] = 0;

	if (KeyEnter.pressed())myKeyboard[(int)keyboard_num::Enter] = 1;
	else myKeyboard[(int)keyboard_num::Enter] = 0;
}
void myInput::update_input_controller()
{
	if (const auto gamepad = Gamepad(controller_index)) // 接続されていたら
	{
		const auto& info = gamepad.getInfo();

		for (auto [i, button] : Indexed(gamepad.buttons))
		{
			if (button.pressed())gamepad_button[i] = 1;//ボタンが押されている間は1
			else gamepad_button[i] = 0;//ボタンを押していない間はゼロ
		}

		for (auto [i, axe] : Indexed(gamepad.axes))
		{
			gamepad_axe[i] = axe;
		}
	}
}

void myInput::update_myButton()
{
	int new_myButton[(int)myButton_num::size];
	for (int i = 0; i < (int)myButton_num::size; i++)new_myButton[i] = 0;
	double new_mySlidePad[(int)mySlidePad_num::size - 4];
	for (int i = 0; i < (int)mySlidePad_num::size - 4; i++)new_mySlidePad[i] = 0;

	if (controller_index == -1)return;
	else if (controller_index == 16)
	{
		for (int i = 0; i < (int)keyboard_num::size; i++)
		{
			for (int j = 0; j < (int)myButton_num::size; j++)
			{
				if (setting_myKeyboard[i] == j)
				{
					new_myButton[j] = Max(new_myButton[j], myKeyboard[i]);
				}
			}
			for (int j = 0; j < (int)mySlidePad_num::size; j++)
			{
				if (setting_myKeyboard[i] == j + 100)
				{
					if ((int)mySlidePad_num::LX <= j && j <= (int)mySlidePad_num::RY) new_mySlidePad[j] = myKeyboard[i] > 0 ? 1 : new_mySlidePad[j];
					if ((int)mySlidePad_num::rLX <= j && j <= (int)mySlidePad_num::rRY) new_mySlidePad[j - 4] = myKeyboard[i] > 0 ? -1 : new_mySlidePad[j - 4];
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < (int)myButton_num::size; j++)
			{
				if (setting_gamepad_button[i] == j)
				{
					new_myButton[j] = Max(new_myButton[j], gamepad_button[i]);
				}
			}
			for (int j = 0; j < (int)mySlidePad_num::size; j++)
			{
				if (setting_gamepad_button[i] == j + 100)
				{
					if ((int)mySlidePad_num::LX <= j && j <= (int)mySlidePad_num::RY) new_mySlidePad[j] = gamepad_button[i] == 1 ? 1 : new_mySlidePad[j];
					if ((int)mySlidePad_num::rLX <= j && j <= (int)mySlidePad_num::rRY) new_mySlidePad[j - 4] = gamepad_button[i] == 1 ? -1 : new_mySlidePad[j - 4];
				}
			}
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < (int)myButton_num::size; j++)
			{
				if (setting_gamepad_axe[i] == j)
				{
					if ((int)mySlidePad_num::LX <= i && i <= (int)mySlidePad_num::RY) new_myButton[j] = gamepad_axe[i] > 0.8 ? 1 : new_myButton[j];
					if ((int)mySlidePad_num::rLX <= i && i <= (int)mySlidePad_num::rRY) new_myButton[j] = gamepad_axe[i - 4] < -0.8 ? 1 : new_myButton[j];
				}
			}
			for (int j = 0; j < (int)mySlidePad_num::size; j++)
			{
				if (setting_gamepad_axe[i] == j + 100)
				{
					if ((int)mySlidePad_num::LX <= j && j <= (int)mySlidePad_num::RY)
						if(gamepad_axe[i] < -mySlidePad_deadzoon || mySlidePad_deadzoon < gamepad_axe[i])new_mySlidePad[j] = gamepad_axe[i];
					if ((int)mySlidePad_num::rLX <= j && j <= (int)mySlidePad_num::rRY)
						if (gamepad_axe[i] < -mySlidePad_deadzoon || mySlidePad_deadzoon < gamepad_axe[i])new_mySlidePad[j - 4] = -gamepad_axe[i];
				}
			}
		}
	}

	for (int i = 0; i < (int)myButton_num::size; i++)
	{
		myButton[i] = new_myButton[i];
	}
	for (int i = 0; i < (int)mySlidePad_num::size - 4; i++)
	{
		mySlidePad[i] = new_mySlidePad[i];
	}
	
}

void myInput::setting_controller()
{

	//Print << controller_index;
}
void myInput::save_setting_controller1()
{
	// 書き込み用のバイナリファイルをオープン
	Serializer<BinaryWriter> writer{ U"data/setting_controller/setting_controller1.bin" };

	if (not writer) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `setting_controller1.bin`" };
	}

	// バイナリファイルにシリアライズ対応型のデータを書き込む
	for (int i = 0; i < 20; i++)
	{
		writer(setting_gamepad_button[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		writer(setting_gamepad_axe[i]);
	}
	for (int i = 0; i < (int)keyboard_num::size; i++)
	{
		writer(setting_myKeyboard[i]);
	}
}
void myInput::load_setting_controller1()
{
	// バイナリファイルをオープン
	Deserializer<BinaryReader> reader{ U"data/setting_controller/setting_controller1.bin" };

	if (not reader) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `setting_controller1.bin`" };
	}


	// バイナリファイルからシリアライズ対応型のデータを読み込む
	for (int i = 0; i < 20; i++)
	{
		reader(setting_gamepad_button[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		reader(setting_gamepad_axe[i]);
	}
	for (int i = 0; i < (int)keyboard_num::size; i++)
	{
		reader(setting_myKeyboard[i]);
	}
}

bool myInput::press_any_myButton()
{
	bool check = false;
	for (int i = 0; i < (int)myButton_num::size; i++)
	{
		if (myButton[i] > 0)check = true;
	}
	if (check)return true;
	return false;
}

void myInput::ini_Input()
{
	for (int i = 0; i < 20; i++)
	{
		gamepad_button[i] = 0;
	}
	for (int i = 0; i < 8; i++)
	{
		gamepad_axe[i] = 0;
	}
	for (int i = 0; i < (int)keyboard_num::size; i++)
	{
		myKeyboard[i] = 0;
	}


	for (int i = 0; i < 17; i++)
	{
		myButton[i] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		mySlidePad[i] = 0;
	}
}
void myInput::ini_setting()
{
	for (int i = 0; i < 20; i++)setting_gamepad_button[i] = -1;
	for (int i = 0; i < 8; i++)setting_gamepad_axe[i] = -1;
	for (int i = 0; i < (int)keyboard_num::size; i++)setting_myKeyboard[i] = -1;
}
void myInput::ini_keyboard()
{
	ini_setting();
	setting_myKeyboard[(int)keyboard_num::Space] = (int)myButton_num::B;
	setting_myKeyboard[(int)keyboard_num::Enter] = (int)myButton_num::A;
	setting_myKeyboard[(int)keyboard_num::n1] = (int)myButton_num::Y;
	setting_myKeyboard[(int)keyboard_num::n2] = (int)myButton_num::X;
	setting_myKeyboard[(int)keyboard_num::n4] = (int)myButton_num::L;
	setting_myKeyboard[(int)keyboard_num::n3] = (int)myButton_num::R;
	setting_myKeyboard[(int)keyboard_num::q] = (int)myButton_num::Home;
	setting_myKeyboard[(int)keyboard_num::Up] = (int)myButton_num::Up;
	setting_myKeyboard[(int)keyboard_num::Right] = (int)myButton_num::Right;
	setting_myKeyboard[(int)keyboard_num::Down] = (int)myButton_num::Down;
	setting_myKeyboard[(int)keyboard_num::Left] = (int)myButton_num::Left;

	setting_myKeyboard[(int)keyboard_num::w] = 100 + (int)mySlidePad_num::LY;
	setting_myKeyboard[(int)keyboard_num::d] = 100 + (int)mySlidePad_num::LX;
	setting_myKeyboard[(int)keyboard_num::s] = 100 + (int)mySlidePad_num::rLY;
	setting_myKeyboard[(int)keyboard_num::a] = 100 + (int)mySlidePad_num::rLX;

}
void myInput::ini_joy_con_L()
{
	ini_setting();
	setting_gamepad_button[0] = (int)myButton_num::B;
	setting_gamepad_button[1] = (int)myButton_num::A;
	setting_gamepad_button[2] = (int)myButton_num::Y;
	setting_gamepad_button[3] = (int)myButton_num::X;
	setting_gamepad_button[4] = (int)myButton_num::L;
	setting_gamepad_button[5] = (int)myButton_num::R;
	setting_gamepad_button[8] = (int)myButton_num::Home;
	setting_gamepad_button[16] = (int)myButton_num::Up;
	setting_gamepad_button[17] = (int)myButton_num::Right;
	setting_gamepad_button[18] = (int)myButton_num::Down;
	setting_gamepad_button[19] = (int)myButton_num::Left;
}
void myInput::ini_joy_con_R()
{
	ini_setting();
	setting_gamepad_button[0] = (int)myButton_num::B;
	setting_gamepad_button[1] = (int)myButton_num::A;
	setting_gamepad_button[2] = (int)myButton_num::Y;
	setting_gamepad_button[3] = (int)myButton_num::X;
	setting_gamepad_button[4] = (int)myButton_num::L;
	setting_gamepad_button[5] = (int)myButton_num::R;
	setting_gamepad_button[9] = (int)myButton_num::Home;
	setting_gamepad_button[16] = (int)myButton_num::Up;
	setting_gamepad_button[17] = (int)myButton_num::Right;
	setting_gamepad_button[18] = (int)myButton_num::Down;
	setting_gamepad_button[19] = (int)myButton_num::Left;
}
void myInput::ini_joy_con_L2()
{
	ini_setting();
	setting_gamepad_button[16] = 100 + (int)mySlidePad_num::LX;
	setting_gamepad_button[17] = 100 + (int)mySlidePad_num::rLY;
	setting_gamepad_button[18] = 100 + (int)mySlidePad_num::rLX;
	setting_gamepad_button[19] = 100 + (int)mySlidePad_num::LY;
	setting_gamepad_button[10] = (int)myButton_num::PadL;
	setting_gamepad_button[0] = (int)myButton_num::Left;
	setting_gamepad_button[1] = (int)myButton_num::Down;
	setting_gamepad_button[2] = (int)myButton_num::Up;
	setting_gamepad_button[3] = (int)myButton_num::Right;
	setting_gamepad_button[14] = (int)myButton_num::L;
	setting_gamepad_button[15] = (int)myButton_num::L2;
	setting_gamepad_button[8] = (int)myButton_num::Opt2;
}
void myInput::ini_joy_con_R2()
{
	ini_setting();
	setting_gamepad_button[0] = (int)myButton_num::A;
	setting_gamepad_button[1] = (int)myButton_num::X;
	setting_gamepad_button[2] = (int)myButton_num::B;
	setting_gamepad_button[3] = (int)myButton_num::Y;
	setting_gamepad_button[16] = 100 + (int)mySlidePad_num::rRX;
	setting_gamepad_button[17] = 100 + (int)mySlidePad_num::RY;
	setting_gamepad_button[18] = 100 + (int)mySlidePad_num::RX;
	setting_gamepad_button[19] = 100 + (int)mySlidePad_num::rRY;
	setting_gamepad_button[11] = (int)myButton_num::PadR;
	setting_gamepad_button[14] = (int)myButton_num::R;
	setting_gamepad_button[15] = (int)myButton_num::R2;
	setting_gamepad_button[12] = (int)myButton_num::Home;
	setting_gamepad_button[9] = (int)myButton_num::Opt1;
	
}
void myInput::ini_kasai()
{
	ini_setting();
	setting_gamepad_button[0] = (int)myButton_num::Y;
	setting_gamepad_button[1] = (int)myButton_num::B;
	setting_gamepad_button[2] = (int)myButton_num::A;
	setting_gamepad_button[3] = (int)myButton_num::X;
	setting_gamepad_button[4] = (int)myButton_num::L;
	setting_gamepad_button[5] = (int)myButton_num::R;
	setting_gamepad_button[6] = (int)myButton_num::L2;
	setting_gamepad_button[7] = (int)myButton_num::R2;
	setting_gamepad_button[8] = (int)myButton_num::Opt2;
	setting_gamepad_button[9] = (int)myButton_num::Opt1;
	setting_gamepad_button[10] = (int)myButton_num::PadL;
	setting_gamepad_button[11] = (int)myButton_num::PadR;
	setting_gamepad_button[12] = (int)myButton_num::Home;
	setting_gamepad_button[14] = (int)myButton_num::Up;
	setting_gamepad_button[15] = (int)myButton_num::Right;
	setting_gamepad_button[16] = (int)myButton_num::Down;
	setting_gamepad_button[17] = (int)myButton_num::Left;

	setting_gamepad_axe[0] = 100 + (int)mySlidePad_num::LX;
	setting_gamepad_axe[1] = 100 + (int)mySlidePad_num::rLY;
	setting_gamepad_axe[2] = 100 + (int)mySlidePad_num::RX;
	setting_gamepad_axe[3] = 100 + (int)mySlidePad_num::rRY;


	//setting_gamepad_button[14] = 100 + (int)mySlidePad_num::LY;
	//setting_gamepad_button[15] = 100 + (int)mySlidePad_num::LX;
	//setting_gamepad_button[16] = 100 + (int)mySlidePad_num::rLY;
	//setting_gamepad_button[17] = 100 + (int)mySlidePad_num::rLX;

	//setting_gamepad_axe[0] = (int)myButton_num::Right;
	//setting_gamepad_axe[1] = (int)myButton_num::Down;
	//setting_gamepad_axe[4] = (int)myButton_num::Left;
	//setting_gamepad_axe[5] = (int)myButton_num::Up;

}
void myInput::ini_SHIROUS()
{
	ini_setting();
	setting_myKeyboard[(int)keyboard_num::Up] = (int)myButton_num::Up;
	setting_myKeyboard[(int)keyboard_num::Right] = (int)myButton_num::Right;
	setting_myKeyboard[(int)keyboard_num::Down] = (int)myButton_num::Down;
	setting_myKeyboard[(int)keyboard_num::Left] = (int)myButton_num::Left;

	setting_myKeyboard[(int)keyboard_num::z] = (int)myButton_num::A;
	setting_myKeyboard[(int)keyboard_num::x] = (int)myButton_num::B;
	setting_myKeyboard[(int)keyboard_num::c] = (int)myButton_num::L;
	setting_myKeyboard[(int)keyboard_num::Shift] = (int)myButton_num::R;

	setting_myKeyboard[(int)keyboard_num::q] = (int)myButton_num::Home;
}



