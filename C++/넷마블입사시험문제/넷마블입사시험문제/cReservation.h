#pragma once
class cReservation
{
private:
	vector<int> m_vecRoom;
	struct Reservation{
		char name;
		bool iscancel;
	};
	vector<Reservation> m_veccustomer;
public:
	cReservation();
	~cReservation();

	void  Excute(int roomNum/*,vector<Reservation> customer*/);
	
};

