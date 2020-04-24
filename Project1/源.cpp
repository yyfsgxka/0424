#include<iostream>

#include<opencv2/opencv.hpp>

#include<math.h>

using namespace std;

using namespace cv;

int main()

{

	Mat scrM = imread("hogTemplate.jpg", 0);
	Mat img1 = imread("img1.jpg", 0);
	Mat img2 = imread("img2.jpg", 0);
	int count = 0;
	int temp = 0;
	
	scrM.convertTo(scrM, CV_32F, 1 / 255.0);
	img1.convertTo(img1, CV_32F, 1 / 255.0);
	img2.convertTo(img2, CV_32F, 1 / 255.0);

	int blocksize = 16;
	int nx = scrM.cols / blocksize;
	int ny = scrM.rows / blocksize;

	int bins = nx*ny * 8;
	//����
	float ref_his[720] = { 0 };
	float his1[720] = { 0 };
	float his2[720] = { 0 };

	

	Mat gx, gy;
	Mat mag, angle;

	Mat cell = Mat(Size(16, 16), CV_32F);
	Mat cell1 = Mat(Size(16, 16), CV_32F);

	Sobel(scrM, gx, CV_32F, 1, 0, 1);
	Sobel(scrM, gy, CV_32F, 0, 1, 1);
	//����ݶȺͽǶ�
	cartToPolar(gx, gy, mag, angle, true);
	

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			
        for (int a = j * blocksize; a < (j + 1)*blocksize; a++) {
		for (int b = i * blocksize; b < (i + 1)*blocksize; b++) {
			int angle1 = 0;//
			float angle2 = angle.at<float>(a, b);	//���صĽǶ�ֵ
			angle1 = angle2 / 45;	//�Ƕ�λ��
			float mag1 = mag.at<float>(a, b);		//���صķ���ֵ
			ref_his[angle1 + count * 8] += mag1;				//������ĽǶ�λ�����ӷ���ֵ
		}
	}
	count++;//��ѭ����ʼ��һ��cell�Ĳ���
		}

	}

	//��һ��ͼ����

	int count1 = 0;
	int temp1 = 0;

	Mat gx1, gy1;
	Mat mag1, angle1;

	Mat cell2 = Mat(Size(16, 16), CV_32F);

	Mat cell3 = Mat(Size(16, 16), CV_32F);

	Sobel(img1, gx1, CV_32F, 1, 0, 1);
	Sobel(img1, gy1, CV_32F, 0, 1, 1);

	cartToPolar(gx1, gy1, mag1, angle1, true);

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			for (int a = j * blocksize; a < (j + 1)*blocksize; a++) {
				for (int b = i * blocksize; b < (i + 1)*blocksize; b++) {
					int angle_img1 = 0;//
					float angle2_img1 = angle.at<float>(a, b);	//���صĽǶ�ֵ
					angle_img1= angle2_img1 / 45;	//�Ƕ�λ��
					float mag2 = mag.at<float>(a, b);		//���صķ���ֵ
					his1[angle_img1 + count1 * 8] += mag2;				//������ĽǶ�λ�����ӷ���ֵ
				}
			}
			count1++;//��ѭ����ʼ��һ��cell�Ĳ���

		}

	}

	//������ͼ����

	int count2 = 0;
	int temp2 = 0;

	Mat gx2, gy2;
	Mat mag2, angle2;

	Mat cell4 = Mat(Size(16, 16), CV_32F);
	Mat cell5 = Mat(Size(16, 16), CV_32F);
	Sobel(img2, gx2, CV_32F, 1, 0, 1);
	Sobel(img2, gy2, CV_32F, 0, 1, 1);
	cartToPolar(gx2, gy2, mag2, angle2, true);

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			for (int a = j * blocksize; a < (j + 1)*blocksize; a++) {
				for (int b = i * blocksize; b < (i + 1)*blocksize; b++) {
					int angle1_img2 = 0;//
					float angle2_img = angle.at<float>(a, b);	//���صĽǶ�ֵ
					angle1_img2 = angle2_img / 45;	//�Ƕ�λ��
					float mag1_img2 = mag.at<float>(a, b);		//���صķ���ֵ
					ref_his[angle1_img2 + count2 * 8] += mag1_img2;				//������ĽǶ�λ�����ӷ���ֵ
				}
			}
			count2++;//��ѭ����ʼ��һ��cell�Ĳ���
		}

	}

	//ŷ����ù�ʽ
	int rest1 = 0;
	int rest2 = 0;

	for (int i = 0; i < 720; i++) {

		rest1 = rest1 + (ref_his[i] - his1[i])*(ref_his[i] - his1[i]);
		rest2 = rest2 + (ref_his[i] - his2[i])*(ref_his[i] - his2[i]);

	}

	rest1 = sqrt(rest1);

	rest2 = sqrt(rest2);

	cout << rest1 << endl;

	cout << rest2 << endl;

	if (rest1 < rest2) {

		cout << "ͼƬһ��ο�ͼƬƥ��Ƚϸ�" << endl;

	}

	else {

		cout << "ͼƬ����ο�ͼƬƥ��Ƚϸ�" << endl;

	}

	waitKey(0);

	system("pause");

}