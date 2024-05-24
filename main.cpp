#include <iostream>
#include <thread>
#include "BigFloat.h"

using namespace std;

unsigned int STOP_AT = 1024;
unsigned int PREC = 512;

/*

	PI = 
		+ 6348 2852		Monday
		+ 1180 4193		India
		+ 2372 4246		Asia
		+ 1436 39307	Greed
		+ 1924 55603	Pacific
		+ 2500 211050	Giza
		- 2832 390112	Doc

*/

BigFloat unit = 1;

BigFloat Monday = 0, India = 0, Asia = 0, Greed = 0, Pacific = 0, Giza = 0, Doc = 0;
BigFloat pi = 0;

void reporter(int i)
{
	pi = (Monday * 6348)
		+ (India * 1180)
		+ (Asia * 2372)
		+ (Greed * 1436)
		+ (Pacific * 1924)
		+ (Giza * 2500)
		- (Doc * 2832);

	cout << i << ": " << pi << endl << endl;
}

void arctg(BigFloat& output, BigFloat denominator, bool report = false, int resume_at = 0, int log_at = 50)
{
	output.SetPrecision(PREC);
	int sign = pow(-1, resume_at);
	for (int i = resume_at; i < STOP_AT; i++)
	{
		BigFloat d;
		//d.SetPrecision(PREC);
		d = BigFloat::Power(denominator, 2*i + 1, 1024) * (2 * i + 1);
		output += (unit / d) * sign;
		sign = -sign;

		if (report && i % log_at == 0)
		{
			reporter(i);
		}
	}
}

int main()
{

	cin >> PREC >> STOP_AT;

	unit.SetPrecision(PREC);
	
	thread th_monday([]() { arctg(Monday, 2852); });
	thread th_india([]() { arctg(India, 4193); });
	thread th_asia([]() { arctg(Asia, 4246); });
	thread th_greed([]() { arctg(Greed, 39307); });
	thread th_pacific([]() { arctg(Pacific, 55603); });
	thread th_giza([]() { arctg(Giza, 211050); });
	thread th_doc([]() { arctg(Doc, 390112, true); });

	th_monday.join();
	th_india.join();
	th_asia.join();
	th_greed.join();
	th_pacific.join();
	th_giza.join();
	th_doc.join();

	// Random comment

	return 0;
}