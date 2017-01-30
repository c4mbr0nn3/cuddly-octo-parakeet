#pragma once
#include <string>

using namespace std;

class City
{
public:
	City() {
		Name = "0";
		Lat = 0;
		Long = 0;
	}
	City(string name, double lat, double lon) {
		Name = name;
		Lat = lat;
		Long = lon;
	}
	~City() {}
	void setName(string name) { Name = name; }
	void setLat(double lat) { Lat = lat; }
	void setLong(double lon) { Long = lon; }
	string getName() { return Name; }
	double getLat() { return Lat; }
	double getLong() { return Long; }
private:
	string Name;
	double Lat;
	double Long;
};

