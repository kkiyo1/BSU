#pragma once

static unsigned int count;

void getCount();

class Human {
protected:
	const std::string name;
	const int id;
public:
	Human();
	Human(const std::string& n);
	Human(const std::string& n, const int& i);
	~Human();
	virtual void getData(void) = 0;
};

class Student : protected Human {
protected:
	int course;
public:
	Student();
	Student(const std::string& n,const int& c,const int& i);
	Student(const Student& st);
	~Student();
	void getData();
};

class Diplomist : public Student {
protected:
	std::string topic;
public:
	Diplomist();
	Diplomist(const std::string& n, const int& c, const int& i, const std::string& t);
	Diplomist(const Student& st);
	Diplomist(const Student& st, const std::string& t);
	~Diplomist();
	void getData();
	void setTopic(const std::string& s);
};