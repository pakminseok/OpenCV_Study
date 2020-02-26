#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	CascadeClassifier face_classifier;
	face_classifier.load("haarcascade_frontalface_alt.xml");
	Mat frame;

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "can not open cam" << endl;
		return 0;
	}
	
	while(true)
	{
		cap >> frame;
		if (frame.empty())
			break;
		
		Mat frame2gray;
		cvtColor(frame, frame2gray, COLOR_BGR2GRAY);
		vector<Rect> faces;
		face_classifier.detectMultiScale(frame2gray, faces, 1.1, 3, 0, Size(100, 100));

		if (!faces.empty())
			frame = frame(Rect(faces[0].x, faces[0].y, faces[0].width, faces[0].height));

		resize(frame, frame, Size(256, 256), 0, 0);
		imshow("Detection", frame);

		int ckey = waitKey(30);
		if (ckey == 27)
		{
			cap.release();
			destroyAllWindows();
			break;
		}
	}
	return 0;
}