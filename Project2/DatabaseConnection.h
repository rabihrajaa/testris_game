#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>
#include <vcclr.h>
#include <iostream>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using namespace System;
using namespace System::Data::SqlClient;

class DatabaseConnection {
public:
	static SqlConnection^ GetConnection();
};

