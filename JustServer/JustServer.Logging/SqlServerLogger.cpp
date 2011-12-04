#include "SqlServerLogger.h"
#include <Windows.h>
#include <sqlext.h>

using namespace std;

namespace JustServer {
namespace Logging {

    SqlServerLogger::SqlServerLogger(const wstring& connectionString)
        :connectionString(connectionString) {}

    void SqlServerLogger::LogMessage(const EventType::Enum eventType, const string& message) const {
        wstring wmessage;
        wmessage.reserve(message.size());

        string::const_iterator messageIt;

        for (messageIt = message.begin(); messageIt != message.end(); ++messageIt) {
            wmessage.push_back(*messageIt);
        }

        LogMessage(eventType, wmessage);
    }

    void SqlServerLogger::LogMessage(const EventType::Enum eventType, const wstring& message) const {
        RETCODE retcode;
        SQLHENV hEnvironment = NULL;
        SQLHDBC hConnection = NULL;

        //TODO: error handling

        // Allocate environment handle
        retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnvironment);

        // Set the ODBC version environment attribute
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            retcode = SQLSetEnvAttr(hEnvironment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0); 

            // Allocate connection handle
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                retcode = SQLAllocHandle(SQL_HANDLE_DBC, hEnvironment, &hConnection); 

                // Set login timeout to 5 seconds
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                    SQLSetConnectAttr(hConnection, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

                    SQLTCHAR retConnectionString[2048];

                    SQLSMALLINT retConnectionStringLen;

                    retcode = SQLDriverConnect(
                        hConnection, 
                        NULL, 
                        (SQLTCHAR*)connectionString.c_str(),
                        connectionString.length(),
                        retConnectionString,
                        2048, 
                        &retConnectionStringLen,
                        SQL_DRIVER_NOPROMPT);

                    SQLHSTMT hStatement;

                    // Allocate statement handle
                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hConnection, &hStatement); 

                        // Prepare statement
                        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                            SQLHDESC hIpd = NULL;
                            SQLINTEGER cbValue = SQL_NTS;
                            
                            //first parameter
                            int eventTypeId = eventType;
                            retcode = SQLBindParameter(
                                hStatement, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &eventTypeId, sizeof(int), &cbValue);
                        
                            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                                //second parameter
                                size_t messageLength = message.length();
                                retcode = SQLBindParameter(
                                    hStatement, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WLONGVARCHAR, messageLength, 0, (SQLPOINTER)message.c_str(), messageLength * sizeof(TCHAR), &cbValue);

                                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                                    retcode = SQLExecDirect(hStatement, TEXT("{ call AddEvent(?,?) }"), SQL_NTS);
                                }
                            }

                            SQLFreeHandle(SQL_HANDLE_STMT, hStatement);
                        }

                        SQLDisconnect(hConnection);
                    }

                    SQLFreeHandle(SQL_HANDLE_DBC, hConnection);
                }
            }

            SQLFreeHandle(SQL_HANDLE_ENV, hEnvironment);
        }
    }

}
}