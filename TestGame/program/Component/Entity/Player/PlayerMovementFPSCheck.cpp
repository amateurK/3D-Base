
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// PlayerMovement��FPS�ɂ��ړ����x�̌덷���v������v���O����
// Paiza.io�Ƃ��œ������z��
// 
// �����	: amateurK
// �쐬��	: 2025/01/24
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

			// �`�F�b�N�|�C���g�o��
			if (checktime[checkfhase] <= nowtime) {
				std::cout << "���x:" << speed << " ���W:" << pos << endl;
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
���x:0.164 ���W:0.0328
���x:0.29848 ���W:0.092496
���x:0.573326 ���W:0.388748
���x:0.785881 ���W:1.1062

elapsedtime : 0.0333333
���x:0.180019 ���W:0.021535
���x:0.32997 ���W:0.0754769
���x:0.645582 ���W:0.381985
���x:0.909664 ���W:1.21107

elapsedtime : 0.0166667
���x:0.181533 ���W:0.0202107
���x:0.332956 ���W:0.0733758
���x:0.659129 ���W:0.391305
���x:0.918661 ���W:1.20171

elapsedtime : 0.00833333
���x:0.182285 ���W:0.0195357
���x:0.340202 ���W:0.0751342
���x:0.659291 ���W:0.384916
���x:0.923079 ���W:1.19679

elapsedtime : 0.00416667
���x:0.186126 ���W:0.0199705
���x:0.338072 ���W:0.073163
���x:0.659339 ���W:0.381704
���x:0.924585 ���W:1.19042
*/
/*
	speed += accel * elapsedtime[elapsed];
	speed *= powf(airResistance, elapsedtime[elapsed]);
	pos += speed * elapsedtime[elapsed];

elapsedtime : 0.2
���x:0.126191 ���W:0.0252383
���x:0.205813 ���W:0.0664009
���x:0.307748 ���W:0.23671
���x:0.338523 ���W:0.56813

elapsedtime : 0.0333333
���x:0.154201 ���W:0.0191366
���x:0.251496 ���W:0.0620513
���x:0.376057 ���W:0.260709
���x:0.413971 ���W:0.676636

elapsedtime : 0.0166667
���x:0.157218 ���W:0.018226
���x:0.256415 ���W:0.0611693
���x:0.385017 ���W:0.269092
���x:0.421915 ���W:0.679388

elapsedtime : 0.00833333
���x:0.15874 ���W:0.0177474
���x:0.262153 ���W:0.062878
���x:0.387944 ���W:0.266855
���x:0.425921 ���W:0.68066

elapsedtime : 0.00416667
���x:0.162109 ���W:0.0181777
���x:0.261789 ���W:0.0615373
���x:0.389405 ���W:0.265708
���x:0.427891 ���W:0.679486

*/