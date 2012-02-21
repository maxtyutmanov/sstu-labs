CREATE TABLE Users (
	ID INTEGER PRIMARY KEY NOT NULL,
	Name VARCHAR(100) NOT NULL,
	Password VARCHAR(100) NOT NULL
);

CREATE TABLE Roles (
	ID INTEGER PRIMARY KEY NOT NULL,
	Name VARCHAR(100) NOT NULL
);

CREATE TABLE Users_Roles (
	ID INTEGER PRIMARY KEY NOT NULL,
	UserID INTEGER REFERENCES Users(ID) ON DELETE CASCADE,
	RoleID INTEGER REFERENCES Roles(ID) ON DELETE CASCADE
);