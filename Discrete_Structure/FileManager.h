#pragma once

#include<string>
#include"User.h"
#include"Door.h"
#include<vector>

using namespace std;



class FileManager {
private:
	string userFilePath;
	string doorFilePath;
	string accessLogFilePath;
public:
	FileManager(string userFile = "users.txt", string doorFile = "doors.txt", string logFile = "accesslog.txt");
	vector<User> loadUsers();
	
	bool saveUsers(const vector<User>& users);

	bool addUser(const User& user);

	User findUserById(string userId);


	vector<Door> loadDoors();
	bool saveDoors(const vector<Door>& doors);
	bool addDoor(const Door& door);
	Door findDoorById(string doorId);
	bool fileExists(string filepath);

	string getUsersFilePath() const;
	string getDoorsFilePath() const;
	string getAccessLogFilePath() const;


	vector<User> getUserByRole(string role);
	vector<Door> getDoorByAccessLevel(int level);
	vector<Door> getDoorByType(string type);


};
