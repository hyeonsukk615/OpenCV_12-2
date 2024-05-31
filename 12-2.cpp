/* 1번과제
#include <iostream> // 표준 입출력 라이브러리 헤더 파일을 포함
#include "opencv2/opencv.hpp" // OpenCV 라이브러리 포함
using namespace cv; // OpenCV 네임스페이스 사용
using namespace std; // 표준 네임스페이스(std)를 사용
int main(void){
	Mat src = imread("polygon.bmp", IMREAD_COLOR);
	if (src.empty()) {cerr << "Image load failed!" << endl;return -1;}
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Mat bin;
	threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);// 이진화 수행
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_LIST, CHAIN_APPROX_NONE);// 윤곽선 찾기
	for (int i = 0; i < contours.size(); i++) {
		Scalar color(rand() & 255, rand() & 255, rand() & 255);// 랜덤 색상 생성
		drawContours(src, contours, i, color, 2);// 윤곽선 그리기
	}
	imshow("src", src);
	waitKey(0);
	return 0;
}
1. 이진화: threshold 함수를 사용하여 그레이스케일 이미지를 이진화합니다. 이 때, THRESH_BINARY_INV | THRESH_OTSU를 사용하여 자동으로 임계값을 결정하고, 
이진화된 이미지를 반전시킵니다.(창의 배경(윤곽선) 값을 감지하지 않게 하기 위함)

2. 윤곽선 찾기:findContours 함수를 사용하여 이진화된 이미지에서 윤곽선을 찾습니다. RETR_LIST를 사용하여 모든 윤곽선을 찾고, 
CHAIN_APPROX_NONE을 사용하여 윤곽선을 구성하는 모든 점을 저장합니다.

3.윤곽선 그리기: Scalar를 사용하여 랜덤 색상을 생성합니다. drawContours 함수를 사용하여 원본 이미지 위에 윤곽선을 랜덤 색상으로 그립니다.
*/
/* 2번 과제
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
	uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
	Mat src = Mat(8, 8, CV_8UC1, data) * 255;
	vector<vector<Point>> contours;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
	cout << "외곽선의 갯수: " << contours.size() << endl;
	for (size_t i = 0; i < contours.size(); ++i) {
		cout << i << "번째 외곽선의 점의 좌표:" << endl;
		for (size_t j = 0; j < contours[i].size(); ++j)cout << "" << contours[i][j]<<",";
		cout << endl;
	}
	return 0;
}
1.이미지 데이터 설정: uchar 배열 data에 8x8 이미지 데이터를 설정

2.이미지 행렬 생성: data 배열을 8x8 크기의 8비트 단일 채널 이미지로 변환, 각 값을 255 (즉, 0은 검은색, 1은 흰색이 됩니다).

3. 윤곽선 찾기: 이미지 src에서 윤곽선을 찾습니다. 모든 윤곽선을 찾고, 구성하는 모든 점을 contours 벡터에 찾은 윤곽선 저장

4. 윤곽선 정보 출력: contours.size()를 출력하여 찾은 윤곽선의 개수와 좌표를 출력

*/
/* 3번과제
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
int main(void){
	Mat src = imread("labelex.png", IMREAD_COLOR);
	if (src.empty()) {cerr << "Image load failed!" << endl;return -1;}
	Mat gray,bin;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_LIST, CHAIN_APPROX_NONE);// 윤곽선 찾기
	for (int i = 0; i < contours.size(); i++) {
		Scalar color(0, 0, 255);
		for (size_t j = 0; j < contours[i].size(); j++) {
			Point pt1 = contours[i][j];
			Point pt2 = contours[i][(j + 1) % contours[i].size()]; // 다음 점
			line(src, pt1, pt2, color, 2);
		}
	}
	imshow("src", src);
	waitKey(0);
	return 0;
}
1. 이진화 Otsu 방법을 사용하여 자동으로 임계값을 결정하고, 이진화된 이미지는 흑백으로 변환됩니다.

2.. 윤곽선 찾기: 이미지 src에서 윤곽선을 찾습니다. 모든 윤곽선을 찾고, 구성하는 모든 점을 contours 벡터에 찾은 윤곽선 저장

3. 윤곽선 그리기: 윤곽선을 구성하는 각 점을 순회하면서, 현재 점과 다음 점을 line 함수를 사용하여 빨간색으로 연결합니다. 윤곽선의 마지막 점과 첫 번째 점을 연결하여 곡선을 만듭니다.

*/
/* 4번과제
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
int main(void){
	Mat src = imread("labelex.png", IMREAD_COLOR);
	if (src.empty()) {cerr << "Image load failed!" << endl;return -1;}
	Mat gray, bin;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_LIST, CHAIN_APPROX_NONE);// 윤곽선 찾기
	int maxLength = 0;
	int maxIndex = -1;
	for (int i = 0; i < contours.size(); i++) {
		int length = contours[i].size(); // 외곽선 길이는 점의 개수로 정의
		cout <<  i << "번째 외각선 길이: " << length << endl;
		if (length > maxLength) {maxLength = length;maxIndex = i;}
	}
	if (maxIndex != -1) {
		for (size_t j = 0; j < contours[maxIndex].size(); j++) {
			Point pt1 = contours[maxIndex][j];
			Point pt2 = contours[maxIndex][(j + 1) % contours[maxIndex].size()]; // 다음 점 (마지막 점은 첫 번째 점과 연결)
			line(src, pt1, pt2, Scalar(0, 0, 255), 2); // 빨간색으로 그림
		}
		cout << "길이가 최대인 외각선: " << maxIndex<<"번째, 길이는 " << maxLength << endl;// 최대 길이 및 해당 인덱스 출력
	}
	imshow("src", src);
	waitKey(0);
	return 0;
}

1. 이진화 Otsu 방법을 사용하여 자동으로 임계값을 결정하고, 이진화된 이미지는 흑백으로 변환됩니다.


2.. 윤곽선 찾기: 이미지 src에서 윤곽선을 찾습니다. 모든 윤곽선을 찾고, 구성하는 모든 점을 contours 벡터에 찾은 윤곽선 저장

가장 긴 윤곽선 찾기: 윤곽선의 길이는 윤곽선을 구성하는 점의 개수로 각 길이를 출력하고, 가장 긴 윤곽선을 찾기 위해 최대 길이를 업데이트합니다.

가장 긴 윤곽선 그리기: 윤곽선을 구성하는 각 점을 순회하면서, 현재 점과 다음 점을 line 함수를 사용하여 빨간색으로 연결합니다. 윤곽선의 마지막 점과 첫 번째 점을 연결하여 곡선을 만듭니다.

#include <iostream> // 표준 입출력 라이브러리 포함
#include "opencv2/opencv.hpp" // OpenCV 라이브러리 포함
using namespace std; // 표준 네임스페이스 사용
using namespace cv; // OpenCV 네임스페이스 사용

int main() {
    Mat src = imread("char_c.png", IMREAD_GRAYSCALE); // 이미지를 그레이스케일로 로드
    Mat dst = src.clone(); // 원본 이미지를 복사
    threshold(src, src, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); // 이진화 수행 (오츠 알고리즘 사용)
    cvtColor(dst, dst, COLOR_GRAY2BGR); // 복사된 이미지를 컬러로 변환
    Mat labels, stats, centroids; // 레이블, 통계, 중심점 행렬 선언
    int c = connectedComponentsWithStats(src, labels, stats, centroids); // 연결 요소 레이블링 및 통계 정보 계산
    int* c11 = stats.ptr<int>(1); // 첫 번째 객체의 통계 정보 포인터
    int* c12 = stats.ptr<int>(2); // 두 번째 객체의 통계 정보 포인터
    Rect c1(c11[0] - 1, c11[1] - 1, c11[2] + 3, c11[3] + 3);// 첫 번째와 두 번째 객체의 영역 설정 (조금 더 넓게)
    Rect c2(c12[0] - 1, c12[1] - 1, c12[2] + 3, c12[3] + 3);
    Rect c1r(c11[0] + c11[2] / 2 - 1, c11[1] - 1, c11[2] / 2 + 3, c11[3] + 3);// 객체를 왼쪽과 오른쪽으로 나눈 영역 설정
    Rect c1l(c11[0] - 1, c11[1] - 1, c11[2] / 2 + 3, c11[3] + 3);
    Rect c2r(c12[0] + c12[2] / 2 - 1, c12[1] - 1, c12[2] / 2 + 3, c12[3] + 3);
    Rect c2l(c12[0] - 1, c12[1] - 1, c12[2] / 2 + 3, c12[3] + 3);
    int c1ll, c1rr, c2ll, c2rr; // 연결 요소 개수를 저장할 변수
    c1ll = connectedComponents(src(c1l), labels);// 각 영역에서 연결 요소 개수를 계산
    c1rr = connectedComponents(src(c1r), labels);
    c2ll = connectedComponents(src(c2l), labels);
    c2rr = connectedComponents(src(c2r), labels);
    if (c1ll == 3) {// 첫 번째 객체 왼쪽 부분에 3개의 연결 요소가 있을 경우
        vector<vector<Point>> object_left; // 왼쪽 객체의 외곽선 저장 벡터
        findContours(src(c1), object_left, RETR_LIST, CHAIN_APPROX_NONE); // 외곽선 찾기
        drawContours(dst(c1), object_left, 0, Scalar(255, 0, 0), 2); // 파란색으로 외곽선 그리기
    }
    if (c1rr == 3) {// 첫 번째 객체 오른쪽 부분에 3개의 연결 요소가 있을 경우
        vector<vector<Point>> object_right; // 오른쪽 객체의 외곽선 저장 벡터
        findContours(src(c1), object_right, RETR_LIST, CHAIN_APPROX_NONE); // 외곽선 찾기
        drawContours(dst(c1), object_right, 0, Scalar(0, 0, 255), 2); // 빨간색으로 외곽선 그리기
    }
    if (c2ll == 3) {// 두 번째 객체 왼쪽 부분에 3개의 연결 요소가 있을 경우
        vector<vector<Point>> object_left; // 왼쪽 객체의 외곽선 저장 벡터
        findContours(src(c2), object_left, RETR_LIST, CHAIN_APPROX_NONE); // 외곽선 찾기
        drawContours(dst(c2), object_left, 0, Scalar(255, 0, 0), 2); // 파란색으로 외곽선 그리기
    }
    if (c2rr == 3) {// 두 번째 객체 오른쪽 부분에 3개의 연결 요소가 있을 경우
        vector<vector<Point>> object_right; // 오른쪽 객체의 외곽선 저장 벡터
        findContours(src(c2), object_right, RETR_LIST, CHAIN_APPROX_NONE); // 외곽선 찾기
        drawContours(dst(c2), object_right, 0, Scalar(0, 0, 255), 2); // 빨간색으로 외곽선 그리기
    }
    imshow("src", src); // 원본 이진화 이미지 표시
    imshow("dst", dst); // 결과 이미지 표시
    waitKey(); // 키 입력 대기
    return 0;
}
/*
1. 이진화: Otsu 방법을 사용하여 자동으로 임계값을 결정하고, 이진화된 이미지는 흑백으로 변환됩니다.

2. 연결된 구성 요소 찾기: 이진화된 이미지에서 연결된 구성 요소를 찾습니다. (레이블, 통계 정보, 무게중심 반환)
(stats 배열을 사용하여 경계 사각형(Rect) 정의)

3. 오른쪽 및 왼쪽 영역 설정: 오른쪽 및 왼쪽 부분을 나누는 사각형(Rect) 정의

4.연결된 구성 요소 개수 계산: 각 영역(왼쪽 및 오른쪽)에서 연결된 구성 요소의 개수를 계산

5. 열린 방향 판별 및 외곽선 그리기: 구성 요소의 왼쪽 및 오른쪽 부분의 연결된 구성 요소 개수를 확인하여 열린 방향을 판별
구성 요소의 외곽선을 찾고, 열린 방향에 따라 외곽선을 색칠합니다.(열린 방향(왼쪽) -> 파란색 / 열린 방향(오른쪽) -> 빨간색)

*/
