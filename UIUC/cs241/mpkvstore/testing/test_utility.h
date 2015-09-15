#define BUFFER_LEN 64
#define KEY_DNE "KEY DOES NOT EXIST"
#define KEY_AE "KEY ALREADY EXISTS"
#define WRONG_REV "REVISION NUMBER DOES NOT MATCH"

#define STD_ADD_SUCCESS(i) STD_ADD(i,"true")
#define STD_ADD_FAILURE(i) STD_ADD(i,KEY_AE)
#define STD_ADD2_SUCCESS(i,j) ADD(i,j,"true")

#define STD_UPDATE_SUCCESS(i,j,k) STD_UPDATE(i,j,k,"true")
#define STD_UPDATE_FAIL_KEY(i,j,k) STD_UPDATE(i,j,k,KEY_DNE)
#define STD_UPDATE_FAIL_REV(i,j,k) STD_UPDATE(i,j,k,WRONG_REV)
#define STD_UPDATE2_SUCCESS(i,j,k) UPDATE(i,j,k, "true") 

#define STD_GET_SUCCESS(i,j,k) STD_GET(i,j,k,"true")
#define STD_GET_FAILURE(i,j,k) STD_GET(i,j,k,KEY_DNE)
#define STD_GET2_SUCCESS(i,j,k) GET(i,j,k, "true")
#define STD_GET2_FAILURE(i,j,k) GET(i,j,k,KEY_DNE)

#define STD_DELETE_SUCCESS(i) STD_DELETE(i,"true")
#define STD_DELETE_FAILURE(i) STD_DELETE(i, KEY_DNE)
#define STD_DELETE2_SUCCESS(i) DELETE(i, "true")

void fail(int i);
void success(int i);
int ADD(const char* key, const char* value, const char* success);
int STD_ADD(int i, const char* success);
int UPDATE(const char* key, const char* value, int rev, const char* success);
int STD_UPDATE(int i, int j, int k, const char* success);
int GET(const char* key, const char* value, int rev, const char* success);
int STD_GET(int i, int j, int k, const char* success);
int DELETE(const char* key, const char* success);
int STD_DELETE(int i, const char* success);


