#include "DatabaseConnection.h"

SqlConnection^ DatabaseConnection::GetConnection() {
	String^ connString = "Data Source=DESKTOP-CICAHO1\\SQLEXPRESS01;Initial Catalog=tetris;Integrated Security=True";
	SqlConnection^ connection = gcnew SqlConnection(connString);
	return connection;
}
