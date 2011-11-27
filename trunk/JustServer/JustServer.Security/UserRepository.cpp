#include "UserRepository.h"
#include "DataAccessException.h"
#include <sqlite3.h>

using namespace std;

namespace JustServer {
namespace Http {
namespace Security {

    UserRepository::UserRepository(const std::wstring& databasePath) 
        : databasePath(databasePath) { }

    auto_ptr<User> UserRepository::GetUser(const string& name, const string& password) const {
        sqlite3* pDb = NULL;
        
        //TODO: danger!!!
        int openResult = sqlite3_open16(databasePath.c_str(), &pDb);
        
        if (openResult != SQLITE_OK) {
            throw DataAccessException("Cannot open users database");
        }

        //get all roles of user

        //TODO: beware of SQL injection!
        string statementText = 
           "SELECT R.Name \
            FROM \
                Users U \
            LEFT OUTER JOIN \
                Users_Roles UR ON (U.ID = UR.UserID) \
            INNER JOIN \
                Roles R ON (UR.RoleID = R.ID) \
            WHERE \
                U.Name = '" + name + "' AND \
                U.Password = '" + password + "'";

        sqlite3_stmt* pStmt;

        int prepareResult = sqlite3_prepare_v2(pDb, statementText.c_str(), statementText.size() + 1, &pStmt, NULL);

        if (prepareResult != SQLITE_OK) {
            throw DataAccessException("Error while preparing SQL statement");
        }

        int resultsCount = 0;

        int stepResult;

        vector<string> roles;

        //TODO: error handling
        while ((stepResult = sqlite3_step(pStmt)) == SQLITE_ROW) {
            int roleNameLength = sqlite3_column_bytes(pStmt, 0);

            if (roleNameLength != 0) {
                const char* roleName = (const char*)sqlite3_column_text(pStmt, 0);

                roles.push_back(roleName);
            }

            ++resultsCount;
        }

        auto_ptr<User> result;

        if (resultsCount != 0) {
            //user was found

            result = auto_ptr<User>(new User(name, roles));
        }

        sqlite3_finalize(pStmt);
        sqlite3_close(pDb);

        return result;
    }
}
}
}