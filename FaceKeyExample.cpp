#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	CascadeClassifier face_classifier;
	face_classifier.load("haarcascade_frontalface_alt.xml");
	Mat frame;

	Mat my_face = imread("your_photo.jpg", 0);//size(256,256)이어야 정확성 높음.
	
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
		face_classifier.detectMultiScale(frame2gray, faces, 1.1, 5, 0, Size(80, 80));

		if (!faces.empty())
		{
			Mat face = frame(Rect(faces[0].x, faces[0].y, faces[0].width, faces[0].height));
			resize(face, face, Size(256, 256), 0, 0);
			cvtColor(face, face, COLOR_BGR2GRAY);
			
			matchTemplate(my_face, face, face, TM_SQDIFF_NORMED);
			double minVal;
			Point minLoc;

			minMaxLoc(face, &minVal, NULL, &minLoc, NULL);
			cout << minLoc.x << " " << minLoc.y << " "<<minVal << endl;
			if (minVal > 0.95)
			{
				cout << "Open the Door" << endl;
				cout << "Welcome, Master!!" << endl;
				break;
			}
		}
		
		imshow("Detection", frame);

		if (waitKey(33) > 0)
		{
			cap.release();
			destroyAllWindows();
			break;
		}
	}
	return 0;
}