
/**************************************************************************************************************
 
		exercise:	The Closest Pair of Points Problem
		info:	1st Teamwork exercise
		course subject: Algorithm Design and Analysis
		professor:	Dr. HajAhmadi
		team members:	Parsa KamaliPour 97149081, Hosein Ahmadi 97149003, Narges RafieeZadeh 97149048

***************************************************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int operation = 0;
int compare = 0;

// every point in a plane is a 2D data consisting x , y
struct Point2D
{
	double x;
	double y;
};

Point2D nil;
Point2D minimalAPoint;
Point2D minimalBPoint;

double ClosestPair(vector<Point2D>& p, int size);
double ClosestPairRecursive(vector<Point2D>& Px, vector<Point2D>& Py, int size);
double Distance(Point2D first, Point2D second);
double BruteForceMethod(vector<Point2D>& P, int size);
double ClosestPointInS(vector<Point2D>& S, int size, double d);
void MergeSort(vector<Point2D>& list, int lo, int hi, int sortAxis);
void Merge(vector<Point2D>& list, int lo, int mid, int hi, int sortAxis);

int main()
{
	vector<double> input;

	// { (2, 3) , (12, 30) , (40, 50) , (5, 1), (12, 10) , (3, 4) }

	int size;
	cin >> size;

	double temp;
	for (int i = 0; i < size*2; i++)
	{
		cin >> temp;
		input.push_back(temp);
	}

	vector<Point2D> list;
	Point2D point;

	for (int i = 0; i < input.size(); i += 2)
	{	
		point.x = input[i];
		point.y = input[i + 1];
		list.push_back(point);
	}

	double dist = ClosestPair(list, list.size());
	cout << "smallest distance is : "<< dist << " : point (" <<
		minimalAPoint.x << ", " << minimalAPoint.y << ") "<<
		"to point (" << minimalBPoint.x << ", " << minimalBPoint.y << ")" <<endl;
	cout << "number of point compared is : " << compare << " and number of operations on points are : " <<
		operation << endl;
}

double ClosestPair(vector<Point2D>& P, int size) 
{
	vector<Point2D> Px, Py;

	for (int i = 0; i < size; i++) 
	{
		Px.push_back(P[i]);
		Py.push_back(P[i]);
	}

	MergeSort(Px, 0, size - 1, 1);
	MergeSort(Py, 0, size - 1, 2);

	return ClosestPairRecursive(Px, Py, size);
}

double ClosestPairRecursive(vector<Point2D>& Px, vector<Point2D>& Py, int size) 
{
	if (size <= 3) 
	{
		return BruteForceMethod(Px, size);
	}

	int mid = (size - 1) / 2;
	Point2D midPoint = Px[mid];

	vector<Point2D> Ly;
	vector<Point2D> Ry;

	for (int i = 0; i < size; i++) 
	{
		if (Py[i].x <= midPoint.x)
			Ly.push_back(Py[i]);

		else
			Ry.push_back(Py[i]);
	}

	vector<Point2D> Rx;
	vector<Point2D> Lx;

	for (int i = 0; i <= mid; i++)
		Lx.push_back(Px[i]);

	for (int i = mid + 1; i < size; i++)
		Rx.push_back(Px[i]);

	double dl = ClosestPairRecursive(Lx, Ly, mid);
	double dr = ClosestPairRecursive(Rx, Ry, size - mid - 1);

	double d = (dl < dr) ? dl : dr;

	vector<Point2D> S;

	for (int i = 0; i < size; i++) 
	{
		double abso = 0;

		if ((Py[i].x - midPoint.x) < 0) 
			abso = -(Py[i].x - midPoint.x);

		else 
			abso = (Py[i].x - midPoint.x);

		if (abso < d) 
			S.push_back(Py[i]);
	}

	return ClosestPointInS(S, S.size(), d);
}

double ClosestPointInS(vector<Point2D>& S, int size, double d)
{
	double min = d;

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size && (S[j].y - S[i].y) < min; j++)
		{
			compare++;
			if (Distance(S[i], S[j]) < min)
			{
				min = Distance(S[i], S[j]);
				minimalAPoint = S[i];
				minimalBPoint = S[j];
			}
		}
	}

	return min;
}

double Distance(Point2D first, Point2D second) 
{
	double P1x = first.x;
	double P2x = second.x;
	double P1y = first.y;
	double P2y = second.y;

	operation += 7;

	return sqrt((P1x - P2x) * (P1x - P2x) + (P1y - P2y) * (P1y - P2y));
}

double BruteForceMethod(vector<Point2D>& P, int size)
{
	double min = DBL_MAX;

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			compare++;
			if (Distance(P[i], P[j]) < min)
			{
				min = Distance(P[i], P[j]);
				minimalAPoint = P[i];
				minimalBPoint = P[j];
			}
		}
	}
	return min;
}

void MergeSort(vector<Point2D>& list, int lo, int hi, int sortAxis) 
{
	if (lo < hi)
	{
		int mid = (lo + hi) / 2;
		MergeSort(list, lo, mid, sortAxis);
		MergeSort(list, mid + 1, hi, sortAxis);
		Merge(list, lo, mid, hi, sortAxis);
	}
}

void Merge(vector<Point2D>& list, int lo, int mid, int hi, int sortAxis) 
{

	int Lsize = mid + 1 - lo;
	int Rsize = hi - mid;

	vector<Point2D> left;
	vector<Point2D> right;

	for (int i = 0; i < Lsize; i++)
		left.push_back(list[lo + i]);


	for (int j = 0; j < Rsize; j++)
		right.push_back(list[mid + 1 + j]);

	if (sortAxis == 1)
	{
		nil.x = RAND_MAX + RAND_MAX;
		left.push_back(nil);
		right.push_back(nil);

		int i = 0;
		int j = 0;

		for (int t = lo; t <= hi; t++)
		{
			if (left[i].x <= right[j].x)
			{
				list[t] = left[i];
				i++;
			}
			else
			{
				list[t] = right[j];
				j++;
			}
		}

	}

	else
	{
		nil.y = RAND_MAX + RAND_MAX;
		left.push_back(nil);
		right.push_back(nil);

		int i = 0;
		int j = 0;

		for (int t = lo; t <= hi; t++)
		{
			if (left[i].y <= right[j].y)
			{
				list[t] = left[i];
				i++;

			}
			else
			{
				list[t] = right[j];
				j++;
			}
		}

	}
}