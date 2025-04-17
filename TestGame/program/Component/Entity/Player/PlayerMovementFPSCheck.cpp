
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// PlayerMovementのFPSによる移動速度の誤差を計測するプログラム
// Paiza.ioとかで動かす想定
// 
// 製作者	: amateurK
// 作成日	: 2025/01/24
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#include <iostream>
using namespace std;
int main(void) {
	// Your code here!

	float elapsedtime[] = {
		1.0f / 5.0f,
		1.0f / 30.0f,
		1.0f / 60.0f,
		1.0f / 120.0f,
		1.0f / 240.0f
	};
	int elapsedtimeLength = 5;
	float checktime[] = {
		0.2f,
		0.4f,
		1.0f,
		2.0f
	};
	int checktimeLength = 4;
	const float accel = 1.0f;
	const float airResistance = 0.1f;

	for (int elapsed = 0; elapsed < elapsedtimeLength; elapsed++)
	{
		float speed = 0.0f;
		float pos = 0.0f;
		float nowtime = 0.0f;
		int checkfhase = 0;
		std::cout << "elapsedtime : " << elapsedtime[elapsed] << endl;
		while (true)
		{
			nowtime += elapsedtime[elapsed];
			speed += accel * elapsedtime[elapsed];
			speed *= 1.0 - (1.0 - airResistance) * elapsedtime[elapsed];

			pos += speed * elapsedtime[elapsed];

			// チェックポイント経過
			if (checktime[checkfhase] <= nowtime) {
				std::cout << "速度:" << speed << " 座標:" << pos << endl;
				checkfhase++;
				if (checkfhase == checktimeLength)break;
			}
		}
		cout << endl;
	}
}

/*
	speed += accel * elapsedtime[elapsed];
	speed *= 1.0 - (1.0 - airResistance) * elapsedtime[elapsed];
	pos += speed * elapsedtime[elapsed];

elapsedtime : 0.2
速度:0.164 座標:0.0328
速度:0.29848 座標:0.092496
速度:0.573326 座標:0.388748
速度:0.785881 座標:1.1062

elapsedtime : 0.0333333
速度:0.180019 座標:0.021535
速度:0.32997 座標:0.0754769
速度:0.645582 座標:0.381985
速度:0.909664 座標:1.21107

elapsedtime : 0.0166667
速度:0.181533 座標:0.0202107
速度:0.332956 座標:0.0733758
速度:0.659129 座標:0.391305
速度:0.918661 座標:1.20171

elapsedtime : 0.00833333
速度:0.182285 座標:0.0195357
速度:0.340202 座標:0.0751342
速度:0.659291 座標:0.384916
速度:0.923079 座標:1.19679

elapsedtime : 0.00416667
速度:0.186126 座標:0.0199705
速度:0.338072 座標:0.073163
速度:0.659339 座標:0.381704
速度:0.924585 座標:1.19042
*/
/*
	speed += accel * elapsedtime[elapsed];
	speed *= powf(airResistance, elapsedtime[elapsed]);
	pos += speed * elapsedtime[elapsed];

elapsedtime : 0.2
速度:0.126191 座標:0.0252383
速度:0.205813 座標:0.0664009
速度:0.307748 座標:0.23671
速度:0.338523 座標:0.56813

elapsedtime : 0.0333333
速度:0.154201 座標:0.0191366
速度:0.251496 座標:0.0620513
速度:0.376057 座標:0.260709
速度:0.413971 座標:0.676636

elapsedtime : 0.0166667
速度:0.157218 座標:0.018226
速度:0.256415 座標:0.0611693
速度:0.385017 座標:0.269092
速度:0.421915 座標:0.679388

elapsedtime : 0.00833333
速度:0.15874 座標:0.0177474
速度:0.262153 座標:0.062878
速度:0.387944 座標:0.266855
速度:0.425921 座標:0.68066

elapsedtime : 0.00416667
速度:0.162109 座標:0.0181777
速度:0.261789 座標:0.0615373
速度:0.389405 座標:0.265708
速度:0.427891 座標:0.679486

*/